#include "tiva/gpio.hpp"

using namespace tiva;
using namespace tiva::gpio;

int main()
{
	PortE portE;
	OutputPin<5, PortE> pe5(portE);
	pe5.write(true);

	RxUARTPin<6, PortE> pe6(portE);

	while(1);
	// sysctl::SystemControl systemControl;
	// InputPin<5, PortE> pe5(portE);
	// PortE::Pin<5, Input> pe5(portE);
	// 
	// gpio::RxUartPin<7, gpio::PortE> pe7(portE);
	// gpio::TxUartPin<6, gpio::PortE> pe6(portE);
	// uart::Uart7 uart7(systemControl, pe7, pe6);

	// gpio::InputPin<5, gpio::PortE> pe5(portE);
	// gpio::OutputPin<6, gpio::PortE> pe6(portE);

	// pe6.write(false);
	// while(pe5.read()); // while pe5 is set
	// pe6.write(true);
	// while(!pe5.read()); // while pe5 is not set
	// pe6.write(false);

}