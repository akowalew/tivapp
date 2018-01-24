#pragma once

#include <cstdint>

#include "tiva/gpio/pin.hpp"

#include "driverlib/gpio.h"
#include "driverlib/rom.h"

namespace tiva {
namespace gpio {

class IOutputPin
{
public:
	IOutputPin(const IOutputPin& other) = delete;
	IOutputPin& operator=(const IOutputPin& other) = delete;

	IOutputPin(IOutputPin&& other) = delete;
	IOutputPin& operator=(IOutputPin&& other) = delete;

	bool read() const
	{
		const auto value = GPIOPinRead(_baseAddress, _pinMask);
		return (value & _pinMask);
	}
	
	void write(bool state)
	{
		const auto value = (state ? 0xFF : 0x00);
		GPIOPinWrite(_baseAddress, _pinMask, value);
	}

protected:
	IOutputPin(std::uint32_t baseAddress, std::uint8_t pinMask) noexcept
		:	_baseAddress(baseAddress),
			_pinMask(pinMask)
	{
		setAsOutput();
	}

	void setAsOutput()
	{
		GPIOPinTypeGPIOOutput(_baseAddress, _pinMask);
	}

private:
	const std::uint32_t _baseAddress;
	const std::uint8_t _pinMask;
};

template<size_t PinNumber, typename PortType>
class OutputPin
	:	public Pin<PinNumber, PortType>,
		public IOutputPin
{
public:
	using PinType = Pin<PinNumber, PortType>;

	explicit OutputPin(PortType& port)
		:	PinType::Pin(port),
			IOutputPin(PortType::BaseAddress, PinType::PinMask)
	{}	
};

} // namespace gpio
} // namespace tiva