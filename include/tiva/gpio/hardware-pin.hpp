#pragma once

#include "tiva/gpio/pin.hpp"

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

template<size_t PinNumber, typename PortType>
class HardwarePin
	:	public PortType::template Pin<PinNumber, HardwareFunction>
	// not deriving from IHardwarePin to avoid code bloat
{
public:

protected:
	using PinType = typename PortType::template Pin<PinNumber, HardwareFunction>;

	explicit HardwarePin(PortType& port) noexcept;

	~HardwarePin() noexcept = default;
};

template<size_t PinNumber, typename PortType>
inline
HardwarePin<PinNumber, PortType>::HardwarePin(PortType& port) noexcept
	:	PinType::Pin(port)
{}
	
} // namespace gpio
} // namespace tiva