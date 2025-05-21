#pragma once

#include "decompress.hpp"
#include "utils.hpp"

#include <string>

namespace laby
{
    namespace yk
    {
        struct File
        {
            File(const std::string& pathToFile, uint64_t startingOffset = 0);
            ~File();

            bool initialize();
            bool decompress(laby::byte_array& output);

            const std::string& fileName() const;
            uint64_t fileSizeBytes() const;
            uint64_t offset() const;

            bool hasValidHeader() const;

            laby::byte_array fileData_;
            std::string fileName_;
            uint64_t startingOffset_;
            bool initialized_;

            laby::Format fileFormat_;
            uint32_t compressedSize_;
            uint32_t uncompressedSize_;
        };
    }
}
