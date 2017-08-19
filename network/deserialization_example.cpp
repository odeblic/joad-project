#include "deserialization.hpp"

#include <iostream>

int main(int argc, char ** argv)
{
    char array[100];

    ByteBuffer buffer(array, 100);

    auto x = buffer.Fetch<int>();

    short i;
    for (i = -32768; i < -32760; i++)
    {
        unsigned short *pi = (unsigned short *)&i;
        std::cout << "i=" << i << " pi=" << *pi << std::endl;
    }
}
