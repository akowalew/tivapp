#pragma once

#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"

namespace tiva {

#ifdef TIVA_GPIO_USED
# include "tiva/chip/tm4c123gh6pm/gpio.hpp"
#endif // TIVA_GPIO_USED

#ifdef TIVA_UART_USED
# include "tiva/chip/tm4c123gh6pm/uart.hpp"
#endif // TIVA_UART_USED

} // namespace tiva
