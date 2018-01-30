#pragma once

#include <cstdio>
#include "driverlib/uart.h"

namespace tiva {
namespace uart {

enum class WordLength
{
	EightBits = UART_CONFIG_WLEN_8,
	SevenBits = UART_CONFIG_WLEN_7,
	SixBits   = UART_CONFIG_WLEN_6,
	FiveBits  = UART_CONFIG_WLEN_5
};

} // namespace uart
} // namespace tiva
