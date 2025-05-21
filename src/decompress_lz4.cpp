#include "decompress.hpp"

#include <lz4.h>

#include <iostream>

void laby::decompress::lz4(laby::byte_array& input, laby::byte_array& output)
{
    int32_t decompSize = LZ4_decompress_safe(input.data(), output.data(), input.size(), output.size());
    if (decompSize < 0)
    {
        std::cout << "BIG FAILURE\n";
    }
}
