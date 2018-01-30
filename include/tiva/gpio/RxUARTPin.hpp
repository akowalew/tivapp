#pragma once

#include "tiva/gpio/UARTPin.hpp"

namespace tiva {
namespace gpio {

template<std::size_t PinNumber, typename PortType>
class RxUARTPin
	:	public UARTPin<PinNumber, PortType>
{
public:
	using UARTPinType = UARTPin<PinNumber, PortType>;

	explicit RxUARTPin(PortType& port) noexcept;

	~RxUARTPin() noexcept = default;
};

template<std::size_t PinNumber, typename PortType>
inline
RxUARTPin<PinNumber, PortType>::RxUARTPin(PortType& port) noexcept
	:	UARTPinType::UARTPin(port)
{}

} // namespace gpio
} // namespace tiva
