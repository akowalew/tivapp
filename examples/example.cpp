#include "tiva/tiva.hpp"

using namespace tiva;

int main()
{
	sysctl::SystemControl systemControl;
	gpio::PortE portE(systemControl);
	gpio::RxUartPin<7, gpio::PortE> pe7(portE);
	gpio::TxUartPin<6, gpio::PortE> pe6(portE);
	uart::Uart7 uart7(systemControl, pe7, pe6);

	// gpio::InputPin<5, gpio::PortE> pe5(portE);
	// gpio::OutputPin<6, gpio::PortE> pe6(portE);

	// pe6.write(false);
	// while(pe5.read()); // while pe5 is set
	// pe6.write(true);
	// while(!pe5.read()); // while pe5 is not set
	// pe6.write(false);

	while(1);
}