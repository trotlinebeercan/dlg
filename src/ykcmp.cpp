#include "ykcmp.hpp"

// TODO: Delete me
#include <algorithm>
#include <iostream>

namespace Fields
{
    constexpr std::string_view YKCMPString = "YKCMP_V1";
    constexpr size_t YKCMPStringSize       = YKCMPString.size();
    constexpr size_t FileFormatOffset           = 8;
    constexpr size_t FileSizeCompressedOffset   = 12;
    constexpr size_t FileSizeUncompressedOffset = 16;
    constexpr size_t FileDataStartOffset        = 20;
}


laby::yk::File::File(const std::string& pathToFile, uint64_t startingOffset)
    : fileData_({})
    , fileName_(pathToFile)
    , startingOffset_(startingOffset)
    , initialized_(false)
    , fileFormat_(laby::Format::None)
    , compressedSize_(0)
    , uncompressedSize_(0)
{}

laby::yk::File::~File()
{}

bool laby::yk::File::initialize()
{
    // don't need to initialize twice
    if (initialized_)
        return true;

    // read the full file in
    if (!laby::io::readFileData(fileName_, fileData_))
        return false;

    // remove the starting offset from the data
    laby::byte_array(fileData_.begin() + startingOffset_, fileData_.end()).swap(fileData_);

    // verify this is indeed a yk file
    if (!hasValidHeader())
    {
        fileData_.clear();
        return false;
    }

    // read other, supporting data from the header
    uint32_t fileFormat = laby::uint8_to_uint32(fileData_, Fields::FileFormatOffset);
    fileFormat_ = laby::uint32_to_file_format(fileFormat);
    compressedSize_ = laby::uint8_to_uint32(fileData_, Fields::FileSizeCompressedOffset);
    uncompressedSize_ = laby::uint8_to_uint32(fileData_, Fields::FileSizeUncompressedOffset);

    auto ffmt = laby::file_format_to_string(fileFormat_);
    std::printf("%s = %s - %u - %u\n", fileName_.c_str(), ffmt.c_str(), compressedSize_, uncompressedSize_);

    // remove the header information from the data
    laby::byte_array(fileData_.begin() + Fields::FileDataStartOffset, fileData_.end()).swap(fileData_);

    initialized_ = true;
    return true;
}

bool laby::yk::File::decompress(laby::byte_array& finalOutput)
{
    finalOutput.clear();

    if (!initialize()) return false;

    if (fileFormat_ == laby::Format::SlideV2)
    {
        laby::decompress::slidev2(fileData_, finalOutput);
        return true;
    }
    else if (fileFormat_ == laby::Format::LZ4)
    {
        finalOutput.resize(uncompressedSize_);
        laby::decompress::lz4(fileData_, finalOutput);
    }

    std::cout << "unknown file format\n";
    return false;
}

const std::string& laby::yk::File::fileName() const
{
    return fileName_;
}

uint64_t laby::yk::File::fileSizeBytes() const
{
    return fileData_.size();
}

uint64_t laby::yk::File::offset() const
{
    return startingOffset_;
}

bool laby::yk::File::hasValidHeader() const
{
    // don't look inside an empty vector
    if (fileData_.size() == 0)
        return false;

    // we don't have enough space to check for the header format
    if (fileData_.size() < Fields::YKCMPStringSize)
        return false;

    char magic[Fields::YKCMPStringSize];
    std::memcpy(magic, fileData_.data(), Fields::YKCMPStringSize);
    return std::string(magic, magic + 8) == Fields::YKCMPString;
}
