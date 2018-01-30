#pragma once

#include "tiva/gpio/UARTPin.hpp"

namespace tiva {
namespace gpio {

template<std::size_t PinNumber, typename PortType>
class TxUARTPin
	:	public UARTPin<PinNumber, PortType>
{
public:
	using UARTPinType = UARTPin<PinNumber, PortType>;

	explicit TxUARTPin(PortType& port) noexcept;

	~TxUARTPin() noexcept = default;
};

template<std::size_t PinNumber, typename PortType>
inline
TxUARTPin<PinNumber, PortType>::TxUARTPin(PortType& port) noexcept
	:	UARTPinType::UARTPin(port)
{}

} // namespace gpio
} // namespace tiva
