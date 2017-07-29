#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include <typeinfo>

template <typename T>
void print_header(std::size_t left_size, std::size_t right_size)
{
    std::string left_header(left_size, '-');
    std::string right_header(right_size, '-');

    std::cout << "container with element type: " << typeid(T).name() << std::endl;
    std::cout << "+-" << left_header << "-+-" << right_header << "-+" << std::endl;
}

template <typename T>
void print_footer(std::size_t left_size, std::size_t right_size)
{
    std::string left_header(left_size, '-');
    std::string right_header(right_size, '-');

    std::cout << "+-" << left_header << "-+-" << right_header << "-+" << std::endl;
}

template <typename T>
void print_element(std::size_t left_size, std::size_t right_size, T element)
{
    std::cout << "| " << std::setw(left_size) << std::setfill(' ') << element << " | " << std::setw(right_size) << std::setfill(' ') << element << " |" << std::endl;
}

template <typename C>
void print(C container)
{
    using element_type = typename C::value_type;

    std::size_t left_size = 10;
    std::size_t right_size = 5;

    print_header<element_type>(left_size, right_size);

    for (auto &element : container)
    {
        print_element(left_size, right_size, element);
        //std::cout << "| " << std::setw(left_size) << std::setfill(' ') << element << " |      |" << std::endl;
    }

    print_footer<element_type>(left_size, right_size);
}
