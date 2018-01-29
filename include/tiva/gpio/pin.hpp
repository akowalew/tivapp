#pragma once

#include <type_traits>
#include <cstdint>
#include "tiva/gpio/port.hpp"

namespace tiva {
namespace gpio {

struct PinFunctionBase {};
struct InputFunction : public PinFunctionBase {};
struct OutputFunction : public PinFunctionBase {};
struct InputOutputFunction : public PinFunctionBase {};
struct HardwareFunction : public PinFunctionBase {};

template<std::uint32_t PeripheralId, std::uint32_t BaseAddress>
template<std::size_t _PinNumber, typename _PinFunction>
class Port<PeripheralId, BaseAddress>::Pin
{
public:
	static_assert(_PinNumber >= 0 && _PinNumber <= 7, 
		"_PinNumber must be an integer in range [0; 8)");
	static_assert(std::is_base_of<PinFunctionBase, _PinFunction>::value,
		"_PinFunction must be derived from PinFunctionBase");

	using PortType = Port<PeripheralId, BaseAddress>;
	constexpr static auto PinNumber = _PinNumber;
	using PinFunction = _PinFunction;
	constexpr static std::uint8_t PinMask = (1 << PinNumber);

	constexpr explicit Pin(PortType& port) noexcept
	{
		static_cast<void>(port);
	}
};

} // namespace gpio
} // namespace tiva