#pragma once

#include <cstdint>
#include "driverlib/gpio.h"
#include "driverlib/rom.h"

namespace tiva {
namespace gpio {

enum class Direction : std::uint32_t
{
	In = GPIO_DIR_MODE_IN,
	Out = GPIO_DIR_MODE_OUT,
	HardwareControlled = GPIO_DIR_MODE_HW
};

enum class PadStrength : std::uint32_t
{
	_2milliamper = GPIO_STRENGTH_2MA,   
	_4milliamper = GPIO_STRENGTH_4MA,   
	_6milliamper = GPIO_STRENGTH_6MA,   
	_8milliamper = GPIO_STRENGTH_8MA,   
	_8milliamperSlewRateControl = GPIO_STRENGTH_8MA_SC,
	_10milliamper = GPIO_STRENGTH_10MA,
	_12milliamper = GPIO_STRENGTH_12MA
};

enum class PadMode : std::uint32_t
{
	PushPull = GPIO_PIN_TYPE_STD,  
	PushPullWeakPullUp = GPIO_PIN_TYPE_STD_WPU,
	PushPullWeakPullDown = GPIO_PIN_TYPE_STD_WPD,
	OpenDrain = GPIO_PIN_TYPE_OD,
	AnalogComparator = GPIO_PIN_TYPE_ANALOG,
	HibernateWakeHigh = GPIO_PIN_TYPE_WAKE_HIGH,
	HibernateWakeLow = GPIO_PIN_TYPE_WAKE_LOW
};

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
