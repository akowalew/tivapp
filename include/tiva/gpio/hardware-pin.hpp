#pragma once

#include "tiva/gpio/pin.hpp"

namespace tiva {
namespace gpio {

template<size_t PinNumber, typename PortType>
class HardwarePin
	:	public Pin<PinNumber, PortType>
{
public:
	using PinType = Pin<PinNumber, PortType>;
	using PinType::Pin;
};
	
} // namespace gpio
} // namespace tiva