#pragma once

#include <cstdint>
#include "driverlib/gpio.h"

namespace tiva {
namespace gpio {

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

} // namespace gpio
} // namespace tiva
