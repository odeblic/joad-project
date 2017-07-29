#include "generic_factory.hpp"

#include <iostream>

struct Object : public Factory<Object>
{
    Object()      { std::cout << "Object::Object()"    << std::endl; }
    Object(int n) { std::cout << "Object::Object(int)" << std::endl; }
    ~Object()     { std::cout << "Object::~Object()"   << std::endl; }
};

int main()
{
    auto object1 = Object::make();

    auto object2 = Object::make(123);

    return 0;
}
