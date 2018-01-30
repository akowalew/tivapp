#pragma once

#include "tiva/gpio/Pin.hpp"
#include "tiva/gpio/IInputPin.hpp"

namespace tiva {
namespace gpio {

template<std::size_t PinNumber, typename PortType>
class InputPin
	:	public PortType::template Pin<PinNumber, InputFunction>,
		public IInputPin
{
public:
	using PinType = typename PortType::template Pin<PinNumber, InputFunction>;

	explicit InputPin(PortType& port) noexcept;

	~InputPin() = default;
};

template<std::size_t PinNumber, typename PortType>
inline
InputPin<PinNumber, PortType>::InputPin(PortType& port) noexcept
	:	PinType::Pin(port),
		IInputPin(PortType::BaseAddress, PinType::PinMask)
{}

} // namespace gpio
} // namespace tiva
