#pragma once

#include "tiva/gpio/IPin.hpp"

namespace tiva {
namespace gpio {

class IInputPin
	:	public IPin
{
public:

protected:
	IInputPin(std::uint32_t baseAddress, std::uint8_t pinMask) noexcept;

	~IInputPin() noexcept = default;
};

inline
IInputPin::IInputPin(std::uint32_t baseAddress, std::uint8_t pinMask) noexcept
	:	IPin(baseAddress, pinMask)
{
	setDirection(Direction::In);
	configurePad(PadStrength::_2milliamper, PadMode::PushPull);
}

} // namespace gpio
} // namespace tiva
