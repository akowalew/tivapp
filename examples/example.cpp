#include "tiva/tiva.hpp"
#include "tiva/chip/tm4c123gh6pm.hpp"

using namespace tiva::gpio;
using namespace tiva::uart;

int main()
{
	PortE portE;
	RxUARTPin<7, PortE> pe6(portE);
	TxUARTPin<6, PortE> pe7(portE);
	UART7 uart7(pe6, pe7);

	while(1);
}
