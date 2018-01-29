#pragma once

#include "tiva/gpio/pin.hpp"
#include "tiva/gpio/i-pin.hpp"

#include <cstdint>
#include "driverlib/gpio.h"
#include "driverlib/rom.h"

namespace tiva {
namespace gpio {

class IInputPin
	:	public IPin
{
public:

protected:
	IInputPin(std::uint32_t baseAddress, std::uint8_t pinMask) noexcept;

	~IInputPin() noexcept = default;
};

inline
IInputPin::IInputPin(std::uint32_t baseAddress, std::uint8_t pinMask) noexcept
	:	IPin(baseAddress, pinMask)
{
	setDirection(Direction::In);
	configurePad(PadStrength::_2milliamper, PadMode::PushPull);
}

template<std::size_t PinNumber, typename PortType>
class InputPin
	:	public PortType::template Pin<PinNumber, InputFunction>,
		public IInputPin
{
public:
	using PinType = typename PortType::template Pin<PinNumber, InputFunction>;

	explicit InputPin(PortType& port) noexcept;

	~InputPin() = default;
};

template<std::size_t PinNumber, typename PortType>
inline
InputPin<PinNumber, PortType>::InputPin(PortType& port) noexcept
	:	PinType::Pin(port),
		IInputPin(PortType::BaseAddress, PinType::PinMask)
{}

} // namespace gpio
} // namespace tiva