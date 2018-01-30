#pragma once

#include "tiva/sysctl/IPeripheral.hpp"

#include "tiva/uart/WordLength.hpp"
#include "tiva/uart/StopBits.hpp"
#include "tiva/uart/Parity.hpp"

#include <cstdio>
#include "inc/hw_uart.h"
#include "inc/hw_types.h"
#include "driverlib/uart.h"
#include "driverlib/sysctl.h"

namespace tiva {
namespace uart {

class IUART
	:	public sysctl::IPeripheral
{
public:
	void configure(int clk, int baudRate, WordLength wordLength,
		StopBits stopBits, Parity parity) noexcept;

	void enable() noexcept;

	void disable() noexcept;

	bool isEnabled() noexcept;

	void enableTx() noexcept;

	void disableTx() noexcept;

	bool isTxEnabled() noexcept;

	void enableRx() noexcept;

	void disableRx() noexcept;

	bool isRxEnabled() noexcept;

	void enableInterrupts() noexcept;

	void disableInterrupts() noexcept;

	void maskInterrupts() noexcept;

	void unmaskInterrupts() noexcept;

	void getInterruptsStatus() noexcept;

	void clearInterruptsStatus() noexcept;

protected:
	IUART(std::uint32_t peripheralId, std::uint32_t baseAddress) noexcept;

	~IUART() noexcept;

private:
	const std::uint32_t _baseAddress;
};

inline void
IUART::configure(int clk, int baudRate, WordLength wordLength,
	StopBits stopBits, Parity parity) noexcept
{
	const auto config = static_cast<std::uint32_t>(wordLength)
		| static_cast<std::uint32_t>(stopBits)
		| static_cast<std::uint32_t>(parity);
	UARTConfigSetExpClk(_baseAddress, clk,
		baudRate, config);
}

inline
IUART::IUART(std::uint32_t peripheralId, std::uint32_t baseAddress) noexcept
	:	IPeripheral(peripheralId),
		_baseAddress(baseAddress)
{
	enable();
}

inline
IUART::~IUART() noexcept
{
	disable();
}

inline void
IUART::enable() noexcept
{
	HWREG(_baseAddress + UART_O_CTL) |= (UART_CTL_UARTEN);
}

inline void
IUART::disable() noexcept
{
	HWREG(_baseAddress + UART_O_CTL) &= (~UART_CTL_UARTEN);
}

inline bool
IUART::isEnabled() noexcept
{
	return (HWREG(_baseAddress + UART_O_CTL) & UART_CTL_UARTEN);
}

inline void
IUART::enableTx() noexcept
{
	HWREG(_baseAddress + UART_O_CTL) |= UART_CTL_TXE;
}

inline void
IUART::disableTx() noexcept
{
	HWREG(_baseAddress + UART_O_CTL) &= (~UART_CTL_TXE);
}

inline bool
IUART::isTxEnabled() noexcept
{
	return (HWREG(_baseAddress + UART_O_CTL) & (UART_CTL_TXE));
}

inline void
IUART::enableRx() noexcept
{
	HWREG(_baseAddress + UART_O_CTL) |= UART_CTL_RXE;
}

inline void
IUART::disableRx() noexcept
{
	HWREG(_baseAddress + UART_O_CTL) &= (~UART_CTL_RXE);
}

inline bool
IUART::isRxEnabled() noexcept
{
	return (HWREG(_baseAddress + UART_O_CTL) & (UART_CTL_RXE));
}

} // namespace uart
} // namespace tiva
