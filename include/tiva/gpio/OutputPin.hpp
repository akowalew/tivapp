#pragma once

#include "tiva/gpio/Pin.hpp"
#include "tiva/gpio/IOutputPin.hpp"

namespace tiva {
namespace gpio {

template<std::size_t PinNumber, typename PortType>
class OutputPin
	:	public PortType::template Pin<PinNumber, OutputFunction>,
		public IOutputPin
{
public:
	using PinType = typename PortType::template Pin<PinNumber, OutputFunction>;

	explicit OutputPin(PortType& port) noexcept;

	~OutputPin() noexcept = default;
};

template<std::size_t PinNumber, typename PortType>
inline
OutputPin<PinNumber, PortType>::OutputPin(PortType& port) noexcept
	:	PinType::Pin(port),
		IOutputPin(PortType::BaseAddress, PinType::PinMask)
{}

} // namespace gpio
} // namespace tiva
