#include "generic_convolution.hpp"

#include <string>

int main(int argc, char ** argv)
{
    std::string s1("Doom is an old video game");
    std::string s2("Can you zoom on the video");
    convolution(s1, s2, 3);

    convolution("The rate is same", "My name is Kate", 3);

    convolution("Computer sciences", "Essence of software", 2);

    std::string s("Does this book look related to itself");
    convolution(s, s, 3);

    return 0;
}
