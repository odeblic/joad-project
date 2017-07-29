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
        }
    }

    Reference make() noexcept
    {
        return Reference();
    }
};
