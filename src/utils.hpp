#pragma once

#include <string>
#include <vector>

namespace laby
{
    using byte_array = std::vector<char>;

    /// @brief Takes the next 4 bytes in the input array from provided location and returns the uint32_t rep of them.
    uint32_t uint8_to_uint32(const laby::byte_array& input, size_t at);

    namespace io
    {
        /// @brief Returns the size of file at the provided path in bytes.
        uint64_t getFileSizeBytes(const std::string_view& pathToFile);

        /// @brief Reads the entire file at the provided path and outputs into provided buffer.
        bool readFileData(const std::string& pathToFile, laby::byte_array& outputBuffer);
    }
}
