#pragma once

#include <cstdio>
#include "driverlib/uart.h"

namespace tiva {
namespace uart {

enum class StopBits
{
	One = UART_CONFIG_STOP_ONE,
	Two = UART_CONFIG_STOP_TWO
};

} // namespace uart
} // namespace tiva
