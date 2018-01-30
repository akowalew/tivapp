#pragma once

#include <cstdint>
#include "driverlib/gpio.h"
#include "driverlib/rom.h"

#include "tiva/gpio/Direction.hpp"
#include "tiva/gpio/PadStrength.hpp"
#include "tiva/gpio/PadMode.hpp"

namespace tiva {
namespace gpio {

class IPin
{
public:
	IPin(const IPin& other) noexcept = delete;
	IPin& operator=(const IPin& other) noexcept = delete;

	IPin(IPin&& other) noexcept = delete;
	IPin& operator=(IPin&& other) noexcept = delete;

	bool read() const noexcept;

protected:
	IPin(std::uint32_t baseAddress, std::uint8_t pinMask) noexcept;

	~IPin() noexcept = default;

	void configurePad(PadStrength padStrength, PadMode padMode) noexcept;

	void setDirection(Direction direcion) noexcept;

	const std::uint32_t _baseAddress;
	const std::uint8_t _pinMask;
};

inline bool
IPin::read() const noexcept
{
	const auto value = GPIOPinRead(_baseAddress, _pinMask);
	return (value & _pinMask);
}

inline
IPin::IPin(std::uint32_t baseAddress, std::uint8_t pinMask) noexcept
	:	_baseAddress(baseAddress),
		_pinMask(pinMask)
{}

inline void
IPin::configurePad(PadStrength padStrength, PadMode padMode) noexcept
{
	GPIOPadConfigSet(_baseAddress, _pinMask,
		static_cast<std::uint32_t>(padStrength),
		static_cast<std::uint32_t>(padMode));
}

inline void
IPin::setDirection(Direction direction) noexcept
{
	GPIODirModeSet(_baseAddress, _pinMask,
		static_cast<std::uint32_t>(direction));
}

} // namespace gpio
} // namespace tiva
