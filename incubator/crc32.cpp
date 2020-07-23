#include "crc32.h"

uint32_t crc32(const char *data, unsigned int length)
{
    uint32_t result = 0;
    uint32_t poly = 0x04c11db7;
    for (int i=0; i<length; ++i) {
        uint8_t byte = data[i];
        for (int b=0; b<8; ++b) {
            bool bbit = (byte & 0x80) != 0;
            byte <<= 1;
            bool rbit = (result & 0x80000000) != 0;
            result = (result << 1) | (bbit ? 1 : 0);
            if (rbit) {
                result ^= poly;
            }
        }
    }
    for (int i=0; i<32; ++i) {
        bool rbit = (result & 0x80000000) != 0;
        result <<= 1;
        if (rbit) {
            result ^= poly;
        }
    }
    return result ^ 0xffffffff;
}
