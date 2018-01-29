#pragma once

#include <cstdint>

#include "tiva/gpio/pin.hpp"

#include "driverlib/gpio.h"
#include "driverlib/rom.h"

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

template<size_t PinNumber, typename PortType>
class OutputPin
	:	public PortType::template Pin<PinNumber, OutputFunction>,
		public IOutputPin
{
public:
	using PinType = typename PortType::template Pin<PinNumber, OutputFunction>;

	explicit OutputPin(PortType& port) noexcept;

	~OutputPin() noexcept = default;
};

template<size_t PinNumber, typename PortType>
inline
OutputPin<PinNumber, PortType>::OutputPin(PortType& port) noexcept
	:	PinType::Pin(port),
		IOutputPin(PortType::BaseAddress, PinType::PinMask)
{}

} // namespace gpio
} // namespace tiva