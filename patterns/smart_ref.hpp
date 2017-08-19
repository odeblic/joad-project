#pragma once

#include <functional>
#include <iostream>
#include <mutex>

template<typename T>
class Reference
{
private:
    struct Block
    {
        T object;
        std::uint32_t counter;
    };

    Block * block;

    //static std::vector<Reference> reference_list

public:
    Reference(const Reference & other) noexcept : block(other.block)
    {
        block->counter++;
    }

    Reference(Reference && other) = delete;

    ~Reference() noexcept
    {
        if (--block->counter == 0)
        {
            delete block;
            //remove from reference list
        }
    }

    Reference make() noexcept
    {
        //make object and add to reference list
        return Reference();
    }
};
