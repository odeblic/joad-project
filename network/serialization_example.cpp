#include "serialization.hpp"

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>

int main(int argc, char ** argv)
{
    std::uint8_t byte(5);
    std::uint16_t word(479);
    std::uint32_t dword(1111);
    std::uint64_t qword(485301447);
    std::string str("ABCDEF 0123456789.");

    ByteBuffer buffer;

    buffer.pushU8(byte);
    buffer.pushU16(word);
    buffer.pushU32(dword);
    buffer.pushU64(qword);
    buffer.pushStr(str);

    std::cout << "size: " << buffer.getSize() << std::endl;

    std::cout << "data: ";

    std::uint8_t const * ptr = buffer.getData();

    for (std::size_t index = 0; index < buffer.getSize(); index++)
    {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (int) ptr[index] << " ";
    }

    std::cout << std::endl;

    return 0;
}
