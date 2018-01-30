#include "tiva/tiva.hpp"

#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"

namespace tiva {

namespace gpio {

struct PortE
	:	public Port<SYSCTL_PERIPH_GPIOE, GPIO_PORTE_BASE>
{};

} // namespace gpio

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

} // namespace tiva

using namespace tiva;
using namespace tiva::gpio;
using namespace tiva::uart;

int main()
{
	PortE portE;
	RxUARTPin<7, PortE> pe6(portE);
	TxUARTPin<6, PortE> pe7(portE);
	UART7 uart7(pe6, pe7);

	while(1);
	// sysctl::SystemControl systemControl;
	// InputPin<5, PortE> pe5(portE);
	// PortE::Pin<5, Input> pe5(portE);
	//
	// gpio::RxUARTPin<7, gpio::PortE> pe7(portE);
	// gpio::TxUARTPin<6, gpio::PortE> pe6(portE);
	// uart::UART7 uart7(systemControl, pe7, pe6);

	// gpio::InputPin<5, gpio::PortE> pe5(portE);
	// gpio::OutputPin<6, gpio::PortE> pe6(portE);

	// pe6.write(false);
	// while(pe5.read()); // while pe5 is set
	// pe6.write(true);
	// while(!pe5.read()); // while pe5 is not set
	// pe6.write(false);

}
