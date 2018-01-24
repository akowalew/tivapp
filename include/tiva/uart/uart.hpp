#pragma once

#include "tiva/sysctl/peripheral.hpp"
#include "tiva/sysctl/system-control.hpp"

#include <cstdio>
#include "driverlib/uart.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"

#include "tiva/uart/types.hpp"

namespace tiva {
namespace uart {
	
class IUart
{
protected:
	constexpr IUart(uint32_t baseAddress) noexcept
		:	_baseAddress(baseAddress)
	{}

	void enable() noexcept
	{
		UARTEnable(_baseAddress);
	}

	void configure(int clk, int baudRate, DataSize dataSize,
		StopBits stopBits, Parity parity) noexcept
	{
		const auto config = static_cast<uint32_t>(dataSize)
			| static_cast<uint32_t>(stopBits)
			| static_cast<uint32_t>(parity);
		UARTConfigSetExpClk(_baseAddress, clk, 
			baudRate, config);
	}

private:
	uint32_t _baseAddress;
};
	
template<uint32_t PeripheralId, uint32_t BaseAddress,
	typename RxPinType, typename TxPinType>
class Uart
	:	public sysctl::Peripheral<PeripheralId>,
		public IUart
{
public:
	constexpr Uart(sysctl::SystemControl& systemControl,
			RxPinType& rxPin, TxPinType& txPin) noexcept
		:	sysctl::Peripheral<PeripheralId>::Peripheral(systemControl),
			IUart(BaseAddress)
	{
		static_cast<void>(rxPin);
		static_cast<void>(txPin);
		systemControl.enablePeripheral(*this);
	}
};

#include "tiva/gpio/uart-pin.hpp"

using Uart7Type = Uart<SYSCTL_PERIPH_UART7, UART7_BASE,
	gpio::RxUartPin<7, gpio::PortE>, 
	gpio::TxUartPin<6, gpio::PortE>
>;
struct Uart7
	:	public Uart7Type
{
	using Uart7Type::Uart;
};

} // namespace uart
} // namespace tiva
