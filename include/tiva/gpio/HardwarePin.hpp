#pragma once

#include "tiva/gpio/Pin.hpp"

namespace tiva {
namespace gpio {

template<std::size_t PinNumber, typename PortType>
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

template<std::size_t PinNumber, typename PortType>
inline
HardwarePin<PinNumber, PortType>::HardwarePin(PortType& port) noexcept
	:	PinType::Pin(port)
{}

} // namespace gpio
} // namespace tiva
