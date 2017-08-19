#pragma once

#include <cstdint>
#include <cstring>

class ByteBuffer
{
public:
    ByteBuffer(char const *buffer, std::size_t size)
    : mBuffer(buffer), mSize(size)
    {
    }

    template <typename T>
    T Fetch()
    {
        T fetched;

        if (mSize < sizeof(T))
        {
            // error
        }

        mBuffer += sizeof(T);
        mSize   -= sizeof(T);
        std::memcpy(&fetched, mBuffer, sizeof(T));
        return fetched;
    }

private:
    char const *mBuffer;
    std::size_t mSize;
};
