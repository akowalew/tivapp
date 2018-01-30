#pragma once

#include <cstdio>
#include "driverlib/uart.h"

namespace tiva {
namespace uart {

enum class Parity
{
	None       = UART_CONFIG_PAR_NONE,
	Even       = UART_CONFIG_PAR_EVEN,
	Odd        = UART_CONFIG_PAR_ODD,
	AlwaysOne  = UART_CONFIG_PAR_ONE,
	AlwaysZero = UART_CONFIG_PAR_ZERO
};

} // namespace uart
} // namespace tiva
