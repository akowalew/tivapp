#pragma once

#include "tiva/gpio/pin.hpp"

#include <cstdint>
#include "driverlib/gpio.h"
#include "driverlib/rom.h"

namespace tiva {
namespace gpio {

class IInputPin
{
public:
	IInputPin(const IInputPin& other) = delete;
	IInputPin& operator=(const IInputPin& other) = delete;

	IInputPin(IInputPin&& other) = delete;
	IInputPin& operator=(IInputPin&& other) = delete;

	bool read() const
	{
		const auto value = GPIOPinRead(_baseAddress, _pinMask);
		return (value & _pinMask);
	}

protected:
	IInputPin(std::uint32_t baseAddress, std::uint8_t pinMask) noexcept
		:	_baseAddress(baseAddress),
			_pinMask(pinMask)
	{
		setAsInput();
	}

	void setAsInput()
	{
		GPIOPinTypeGPIOInput(_baseAddress, _pinMask);
	}

private:
	const std::uint32_t _baseAddress;
	const std::uint8_t _pinMask;
};

template<size_t PinNumber, typename PortType>
class InputPin
	:	public Pin<PinNumber, PortType>,
		public IInputPin
{
public:
	using PinType = Pin<PinNumber, PortType>;

	explicit InputPin(PortType& port)
		:	PinType::Pin(port),
			IInputPin(PortType::BaseAddress, PinType::PinMask)
	{}
};

} // namespace gpio
} // namespace tiva