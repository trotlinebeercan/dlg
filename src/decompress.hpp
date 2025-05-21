#pragma once

#include "utils.hpp"

#include <string>
#include <vector>

namespace laby
{
    enum class Format
    {
        // taken from https://github.com/qeedquan/go-media/blob/master/archive/nipponichi/ykcmp.go
        None,
        RLE,
        SlideV1,
        SlideV2,
        Huffman,
        LZ4,
        LZMA,
    };

    inline Format uint32_to_file_format(uint32_t input)
    {
        switch (input)
        {
            case 1: return laby::Format::RLE;
            case 2: return laby::Format::SlideV1;
            case 3: return laby::Format::Huffman;
            case 4: return laby::Format::SlideV2;
            case 8: return laby::Format::LZ4;
            case 9: return laby::Format::LZ4;
            case 10: return laby::Format::LZMA;

            default:
                return laby::Format::None;
        }
    }
    inline std::string file_format_to_string(Format format)
    {
        switch (format)
        {
            case laby::Format::RLE: return "RLE";
            case laby::Format::SlideV1: return "SlideV1";
            case laby::Format::Huffman: return "Huffman";
            case laby::Format::SlideV2: return "SlideV2";
            case laby::Format::LZ4: return "LZ4";
            case laby::Format::LZMA: return "LZMA";

            case laby::Format::None:
            default:
                return "None";
        }
    }

    namespace decompress
    {
        void slidev2(std::vector<char>& inputChar, std::vector<char>& outputChar);
        void lz4(laby::byte_array& input, laby::byte_array& output);
    }
}
