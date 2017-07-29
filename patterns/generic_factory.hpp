#pragma once

#include <memory>

template <typename T>
struct Factory
{
    template<typename ... Args>
    static std::unique_ptr<T> make(Args ... args) // TODO should be noexcept
    {
        //return std::make_unique<T>(std::forward<Args>(args)...);
        return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
};
