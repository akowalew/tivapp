#pragma once

#include "tiva/gpio/IHardwarePin.hpp"

#include <cstdio>
#include "driverlib/pin_map.h"

namespace tiva {
namespace gpio {

class IUARTPin
	:	public IHardwarePin
{
public:

protected:
	IUARTPin(std::uint32_t baseAddress, std::uint8_t pinMask) noexcept;

	~IUARTPin() noexcept = default;
};

inline
IUARTPin::IUARTPin(std::uint32_t baseAddress, std::uint8_t pinMask) noexcept
	:	IHardwarePin(baseAddress, pinMask)
{
	configurePad(PadStrength::_2milliamper, PadMode::PushPull);
	GPIOPinConfigure(GPIO_PE4_U5RX); // TODO: get alternate function
}

} // namespace gpio
} // namespace tiva
