#pragma once

#include <array>
#include <cstdint>
#include <string>

class ByteBuffer
{
public:
    ByteBuffer();
    ~ByteBuffer();

    void pushU8(std::uint8_t);
    void pushU16(std::uint16_t);
    void pushU32(std::uint32_t);
    void pushU64(std::uint64_t);
    void pushFloat(float);
    void pushBytes(char const *, std::size_t);
    void pushStr(std::string const &);

    std::size_t getSize() const;
    std::uint8_t const *getData() const;

private:
    template <typename T>
    void push(T const &);

    static std::uint64_t htonll(std::uint64_t);
    static float htonf(float);

    static std::size_t const PAYLOAD_SIZE_MAX = 1000;

    std::array<std::uint8_t, PAYLOAD_SIZE_MAX> mContent;
    std::size_t mCursor;
    bool mError;
};
