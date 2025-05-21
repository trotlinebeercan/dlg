#include "ykcmp.hpp"

#include <fstream>
#include <iostream>

void runTest(const std::string& input, int32_t offset)
{
    laby::byte_array output;
    laby::yk::File file(input, offset);
    if (!file.decompress(output))
    {
        std::cout << "FAILED\n";
        return;
    }

    std::cout << "PASSED\n";
}

int main(int argc, char* argv[])
{
    runTest("../../data/bu_nachiru_001.dds.phyre", 12);
    runTest("../../data/D6Pleinair.nmbm", 12);
    runTest("../../data/D7Pleinair.nmbm", 12);

    // yay
    return EXIT_SUCCESS;
}
