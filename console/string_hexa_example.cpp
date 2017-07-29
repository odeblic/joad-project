#include "string_hexa.hpp"

#include <iostream>

int main(int argc, char ** argv)
{
    std::string str("This is a string to be displayed in hexadecimal and ASCII format.");

    viewHexadecimal(str, std::cout);

    return 0;
}
