#pragma once

#include "tiva/util/BitSet.hpp"

namespace tiva {
namespace util {

struct BitSetBase {};

template<typename... TBits>
struct BitSet : public BitSetBase
{
    static_assert(areBits<TBits...>());

    constexpr static std::uint32_t Mask = getMaskForBits<TBits...>();

    constexpr BitSet(std::uint32_t value = 0)
        :   _value(value)
    {}

    template<typename... TOtherBits>
    constexpr void set()
    {
        static_assert(containsBits<TOtherBits...>());
        using OtherBitSet = BitSet<TOtherBits...>;
        _value |= (OtherBitSet::Mask);
    }

    template<typename... TOtherBits>
    constexpr void reset()
    {
        static_assert(containsBits<TOtherBits...>());
        using OtherBitSet = BitSet<TOtherBits...>;
        _value &= (~OtherBitSet::Mask);
    }

    template<typename TOtherBit>
    constexpr bool test() const
    {
        static_assert(containsBit<TOtherBit>());
        return (_value & TOtherBit::getMask());
    }

    constexpr bool any() const
    {
        return (_value & Mask);
    }

    constexpr bool all() const
    {
        return ((_value & Mask) == Mask);
    }

    constexpr bool none() const
    {
        return ((_value & Mask) == 0);
    }

    template<typename... TOtherBits>
    constexpr bool anyOf() const
    {
        static_assert(containsBits<TOtherBits...>());
        using OtherBitSet = BitSet<TOtherBits...>;
        return OtherBitSet(_value).any();
    }

    template<typename... TOtherBits>
    constexpr bool allOf() const
    {
        static_assert(containsBits<TOtherBits...>());
        using OtherBitSet = BitSet<TOtherBits...>;
        return OtherBitSet(_value).all();
    }

    template<typename... TOtherBits>
    constexpr bool noneOf() const
    {
        static_assert(containsBits<TOtherBits...>());
        using OtherBitSet = BitSet<TOtherBits...>;
        return OtherBitSet(_value).none();
    }

private:
    template<typename TBit>
    constexpr static bool containsBit()
    {
        return std::disjunction_v<std::is_same<TBit, TBits>...>;
    }

    template<typename TBit>
    constexpr static bool containsBits()
    {
        return containsBit<TBit>();
    }

    template<typename TBit, typename TOtherBit, typename... TOtherBits>
    constexpr static bool containsBits()
    {
        return containsBit<TBit>() && containsBits<TOtherBit, TOtherBits...>();
    }

    std::uint32_t _value;
};

template<typename BitSetType>
constexpr static bool isBitSet()
{
    return std::is_base_of<BitSetBase, BitSetType>();
}

} // namespace util
} // namespace tiva
