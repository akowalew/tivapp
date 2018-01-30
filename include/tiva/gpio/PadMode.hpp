#pragma once

#include <cstdint>
#include "driverlib/gpio.h"

namespace tiva {
namespace gpio {

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

} // namespace gpio
} // namespace tiva
