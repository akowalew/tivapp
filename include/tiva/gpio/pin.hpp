#pragma once

#include <cstdint>
#include "tiva/gpio/port.hpp"

namespace tiva {
namespace gpio {

template<size_t _PinNumber, typename _PortType>
class Pin
{
public:
	using PortType = _PortType;

	static_assert(_PinNumber >= 0 && _PinNumber <= 7, 
		"Pin number must be an integer in range [0; 8)");

	constexpr static auto PinNumber = _PinNumber;
	constexpr static std::uint8_t PinMask = (1 << PinNumber);

	constexpr explicit Pin(PortType& port)
	{
		static_cast<void>(port);
	}
};

} // namespace gpio
} // namespace tiva