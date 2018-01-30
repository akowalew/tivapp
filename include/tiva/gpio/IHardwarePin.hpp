#pragma once

#include "tiva/gpio/IPin.hpp"

namespace tiva {
namespace gpio {

class IHardwarePin
	:	public IPin
{
public:

protected:
	IHardwarePin(std::uint32_t baseAddress,
		std::uint8_t pinMask) noexcept;

	~IHardwarePin() noexcept = default;
};

inline
IHardwarePin::IHardwarePin(std::uint32_t baseAddress,
	std::uint8_t pinMask) noexcept
	:	IPin(baseAddress, pinMask)
{
	setDirection(Direction::HardwareControlled);
}

} // namespace gpio
} // namespace tiva
