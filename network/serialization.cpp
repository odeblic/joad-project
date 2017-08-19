#include "serialization.hpp"

#include <arpa/inet.h>
#include <cstdint>
#include <cstring>
#include <endian.h>
#include <string>

ByteBuffer::ByteBuffer()
: mContent{}, mCursor(0), mError(false)
{
}

ByteBuffer::~ByteBuffer()
{
}

void ByteBuffer::pushU8(std::uint8_t value)
{
    return push(value);
}

void ByteBuffer::pushU16(std::uint16_t value)
{
    return push(htons(value));
}

void ByteBuffer::pushU32(std::uint32_t value)
{
    return push(htonl(value));
}

void ByteBuffer::pushU64(std::uint64_t value)
{
    return push(htonll(value));
}

void ByteBuffer::pushFloat(float value)
{
    return push(htonf(value));
}

void ByteBuffer::pushBytes(char const *buffer, std::size_t size)
{
    if (mCursor + size <= mContent.size())
    {
        std::memcpy(&mContent[mCursor], reinterpret_cast<std::uint8_t const *>(buffer), size);
        mCursor += size;
    }
    else
    {
        mError = true;
    }
}

void ByteBuffer::pushStr(std::string const &value)
{
    pushU16(value.size());
    pushBytes(value.c_str(), value.size());
}

template <typename T>
void ByteBuffer::push(T const &value)
{
    if (mCursor + sizeof(T) <= mContent.size())
    {
        std::memcpy(&mContent[mCursor], &value, sizeof(T));
        mCursor += sizeof(T);
    }
    else
    {
        mError = true;
    }
}

std::size_t ByteBuffer::getSize() const
{
    return !mError ? mCursor : 0;
}

std::uint8_t const *ByteBuffer::getData() const
{
    return !mError ? &mContent[0] : 0;
}

std::uint64_t ByteBuffer::htonll(std::uint64_t value)
{
    if (htons(1) == 1)
    {
        return value;
    }
    else
    {
        std::uint64_t result;

        auto aliasVal = reinterpret_cast<char *>(&value);
        auto aliasRes = reinterpret_cast<char *>(&result);

        aliasRes[0] = aliasVal[7];
        aliasRes[1] = aliasVal[6];
        aliasRes[2] = aliasVal[5];
        aliasRes[3] = aliasVal[4];
        aliasRes[4] = aliasVal[3];
        aliasRes[5] = aliasVal[2];
        aliasRes[6] = aliasVal[1];
        aliasRes[7] = aliasVal[0];

        return result;
    }
}

float ByteBuffer::htonf(float value)
{
    if (htons(1) == 1)
    {
        return value;
    }
    else
    {
        float result;

        auto aliasVal = reinterpret_cast<char *>(&value);
        auto aliasRes = reinterpret_cast<char *>(&result);

        aliasRes[0] = aliasVal[3];
        aliasRes[1] = aliasVal[2];
        aliasRes[2] = aliasVal[1];
        aliasRes[3] = aliasVal[0];

        return result;
    }
}
