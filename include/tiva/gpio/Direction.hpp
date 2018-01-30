#pragma once

#include <cstdint>
#include "driverlib/gpio.h"

namespace tiva {
namespace gpio {
	
enum class Direction : std::uint32_t
{
	In = GPIO_DIR_MODE_IN,
	Out = GPIO_DIR_MODE_OUT,
	HardwareControlled = GPIO_DIR_MODE_HW
};

} // namespace gpio
} // namespace tiva
