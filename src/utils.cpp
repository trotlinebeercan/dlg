#include "utils.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

uint32_t laby::uint8_to_uint32(const laby::byte_array& input, size_t at)
{
    return (static_cast<uint8_t>(input[at]))           +
           (static_cast<uint8_t>(input[at + 1]) << 8)  +
           (static_cast<uint8_t>(input[at + 2]) << 16) +
           (static_cast<uint8_t>(input[at + 3]) << 24);
}

uint64_t laby::io::getFileSizeBytes(const std::string_view& pathToFile)
{
    const std::filesystem::path inputFilePath{pathToFile};
    return std::filesystem::file_size(inputFilePath);
}

bool laby::io::readFileData(const std::string& pathToFile, laby::byte_array& outputBuffer)
{
    auto length = laby::io::getFileSizeBytes(pathToFile);
    if (length == 0)
    {
        std::cout << "Unable to open file for reading, could not get size: " << pathToFile << std::endl;
        return false;
    }

    std::ifstream inputFile(pathToFile, std::ios_base::binary);
    if (!inputFile.is_open())
    {
        std::cout << "Unable to open file for reading, could not open file: " << pathToFile << std::endl;
        return false;
    }

    outputBuffer.clear();
    outputBuffer.resize(length);
    inputFile.read(reinterpret_cast<char*>(outputBuffer.data()), length);
    inputFile.close();
    
    return true;
}
