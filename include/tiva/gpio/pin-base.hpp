#pragma once

namespace tiva {
namespace gpio {
	
class PinBase
{
public:
	PinBase(uint32_t baseAddress, uint8_t pin)
		:	_baseAddress(baseAddress),
			_pin(pin)
	{}

private:
	const uint32_t _baseAddress;
	const uint8_t _pin;
};

} // namespace gpio
} // namespace tiva