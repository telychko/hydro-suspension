#include <iostream>

#include "crc32.h"

int main(int argc, char* argv[])
{
    const char str[] = "0123456789z";
    std::cout << "RESULT:" << std::hex << crc32(str, sizeof(str)-1);
    return 0;
}
