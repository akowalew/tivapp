#pragma once

#include "tiva/gpio/IPin.hpp"

#include <cstdint>
#include "driverlib/gpio.h"

namespace tiva {
namespace gpio {

class IOutputPin
	:	public IPin
{
public:
	void write(bool state) noexcept;

protected:
	IOutputPin(std::uint32_t baseAddress, std::uint8_t pinMask) noexcept;

	~IOutputPin() noexcept = default;
};

inline void
IOutputPin::write(bool state) noexcept
{
	const auto value = (state ? 0xFF : 0x00);
	GPIOPinWrite(_baseAddress, _pinMask, value);
}

inline
IOutputPin::IOutputPin(std::uint32_t baseAddress, std::uint8_t pinMask) noexcept
	:	IPin(baseAddress, pinMask)
{
	setDirection(Direction::Out);
	configurePad(PadStrength::_2milliamper, PadMode::PushPull);
}

} // namespace gpio
} // namespace tiva
