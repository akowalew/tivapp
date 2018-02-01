#pragma once

#include <type_traits>
#include <cstdint>

namespace tiva {
namespace util {

struct BitBase {};

template<std::size_t _Number>
struct Bit : public BitBase
{
    static_assert(_Number >= 0 && _Number <= 31);

    constexpr static auto Number = _Number;

    constexpr static std::uint32_t getMask()
    {
        return (1 << Number);
    }
};

template<typename TBit>
constexpr static bool isBit()
{
    return std::is_base_of_v<BitBase, TBit>;
}

template<typename... TBits>
constexpr static bool areBits()
{
    return std::conjunction_v<std::is_base_of<BitBase, TBits>...>;
}

template<typename TBit>
constexpr static std::uint32_t getMaskForBits()
{
    static_assert(isBit<TBit>());
    return TBit::getMask();
}

template<typename TBit, typename TOtherBit, typename... TOtherBits>
constexpr static std::uint32_t getMaskForBits()
{
    static_assert(isBit<TBit>());
    return TBit::getMask() | getMaskForBits<TOtherBit, TOtherBits...>();
}

} // namespace util
} // namespace tiva
