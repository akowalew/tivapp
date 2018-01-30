#pragma once

#include "tiva/gpio/HardwarePin.hpp"
#include "tiva/gpio/IUARTPin.hpp"

namespace tiva {
namespace gpio {

template<size_t PinNumber, typename PortType>
class UARTPin
	:	public HardwarePin<PinNumber, PortType>,
		public IUARTPin
{
public:

protected:
	using HardwarePinType = HardwarePin<PinNumber, PortType>;

	explicit UARTPin(PortType& port) noexcept;

	~UARTPin() noexcept = default;
};

template<size_t PinNumber, typename PortType>
inline
UARTPin<PinNumber, PortType>::UARTPin(PortType& port)
	:	HardwarePinType::HardwarePin(port),
		IUARTPin(PortType::BaseAddress,
			HardwarePinType::PinType::PinMask)
{}

} // namespace gpio
} // namespace tiva
