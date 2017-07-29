#include "immutable.hpp"

#include <iostream>
#include <sstream>

template <typename T>
std::ostream& operator<<(std::ostream& s, Immutable<T>& x)
{
    s << x.get();
    return s;
}

struct Compound
{
    int a;
    int b;

    Compound(int a, int b) : a(a), b(b)
    {
    }
};

std::ostream& operator<<(std::ostream& s, const Compound& x)
{
    s << "{a=" << x.a << ", b=" << x.b << "}";
    return s;
}

int main()
{
    Immutable<int> immutableInt(-999);
    Immutable<float> immutableFloat(3.1415926);
    Immutable<std::string> immutableString("Who's immutable? Me!");
    Immutable<Compound> immutableCompound(1, 2);

    std::cout << "immutableInt: " << immutableInt << std::endl;
    std::cout << "immutableFloat: " << immutableFloat << std::endl;
    std::cout << "immutableString: " << immutableString << std::endl;
    std::cout << "immutableCompound: " << immutableCompound << std::endl;
}
