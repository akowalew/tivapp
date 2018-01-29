#pragma once

#include "tiva/gpio/hardware-pin.hpp"

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

template<size_t PinNumber, typename PortType>
class RxUARTPin
	:	public UARTPin<PinNumber, PortType>
{
public:
	using UARTPinType = UARTPin<PinNumber, PortType>;

	explicit RxUARTPin(PortType& port) noexcept;

	~RxUARTPin() noexcept = default;
};

template<size_t PinNumber, typename PortType>
inline
RxUARTPin<PinNumber, PortType>::RxUARTPin(PortType& port) noexcept
	:	UARTPinType::UARTPin(port)
{}

template<size_t PinNumber, typename PortType>
class TxUARTPin
	:	public UARTPin<PinNumber, PortType>
{
public:
	using UARTPinType = UARTPin<PinNumber, PortType>;

	explicit TxUARTPin(PortType& port) noexcept;

	~TxUARTPin() noexcept = default;
};

template<size_t PinNumber, typename PortType>
inline
TxUARTPin<PinNumber, PortType>::TxUARTPin(PortType& port) noexcept
	:	UARTPinType::UARTPin(port)
{}

} // namespace gpio
} // namespace tiva