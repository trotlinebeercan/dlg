#include "decompress.hpp"

void laby::decompress::slidev2(std::vector<char>& inputChar, std::vector<char>& outputChar)
{
    auto rIter = outputChar.begin();
    auto dIter = inputChar.begin();
    unsigned int percentage = 0;
    for (; dIter < inputChar.end() && rIter < outputChar.end(); )
    {
        uint8_t tmp = *(dIter++);

        if (tmp < 0x80)
        {
            std::copy(dIter, dIter + tmp, rIter);
            dIter += tmp; rIter += tmp;
        }
        else
        {
            size_t sz, offset;
            if (tmp < 0xC0)
            {
                sz = (tmp >> 4) - 0x8 + 1;
                offset = (tmp & 0x0F) + 1;
            }
            else if (tmp < 0xE0)
            {
                sz = tmp - 0xC0 + 2;
                offset = static_cast<uint8_t>(*(dIter++)) + 1;
            }
            else
            {
                uint8_t tmp2 = *(dIter++);
                uint8_t tmp3 = *(dIter++);
                sz = (tmp << 4) + (tmp2 >> 4) - 0xE00 + 3;
                offset = ((tmp2 & 0x0F) << 8) + tmp3 + 1;
            }

            std::copy(rIter - offset, rIter - offset + sz, rIter);
            rIter += sz;
        }
    }

    outputChar.resize(rIter - outputChar.begin());
}
