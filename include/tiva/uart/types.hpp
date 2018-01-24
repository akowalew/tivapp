#pragma once

#include <cstdio>
#include "driverlib/uart.h"

namespace tiva {
namespace uart {
	
enum class DataSize
{
	EightBits = UART_CONFIG_WLEN_8,
	SevenBits = UART_CONFIG_WLEN_7,
	SixBits   = UART_CONFIG_WLEN_6,
	FiveBits  = UART_CONFIG_WLEN_5
};

enum class StopBits
{
	One = UART_CONFIG_STOP_ONE,
	Two = UART_CONFIG_STOP_TWO
};

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