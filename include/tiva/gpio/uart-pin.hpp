#pragma once

#include "tiva/gpio/hardware-pin.hpp"

#include "driverlib/pin_map.h"

namespace tiva {
namespace gpio {
	
template<size_t PinNumber, typename PortType>
class UartPin
	:	public HardwarePin<PinNumber, PortType>
{
public:
	using HardwarePinType = HardwarePin<PinNumber, PortType>;

	constexpr explicit UartPin(PortType& port)
		:	HardwarePinType::HardwarePin(port)
	{
		configureAsUart();
	}

private:
	void configureAsUart()
	{
		GPIOPinTypeUART(PortType::BaseAddress, 
			HardwarePinType::PinType::PinMask);
		GPIOPinConfigure(GPIO_PE4_U5RX); // at the moment only
	}
};

template<size_t PinNumber, typename PortType>
class RxUartPin
	:	public UartPin<PinNumber, PortType>
{
public:
	using UartPinType = UartPin<PinNumber, PortType>;
	using UartPinType::UartPin;
};

template<size_t PinNumber, typename PortType>
class TxUartPin
	:	public UartPin<PinNumber, PortType>
{
public:
	using UartPinType = UartPin<PinNumber, PortType>;
	using UartPinType::UartPin;
};

} // namespace gpio
} // namespace tiva