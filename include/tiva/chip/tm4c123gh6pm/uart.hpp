#pragma once

namespace uart {

using UART7Type = UART<SYSCTL_PERIPH_UART7, UART7_BASE,
	gpio::RxUARTPin<7, gpio::PortE>,
	gpio::TxUARTPin<6, gpio::PortE>
>;
struct UART7
	:	public UART7Type
{
	using UART7Type::UART;
};

} // namespace uart
