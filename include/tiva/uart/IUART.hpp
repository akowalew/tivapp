#pragma once

#include "tiva/sysctl/IPeripheral.hpp"

#include "tiva/uart/WordLength.hpp"
#include "tiva/uart/StopBits.hpp"
#include "tiva/uart/Parity.hpp"

#include <cstdio>
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

protected:
	IUART(std::uint32_t peripheralId, std::uint32_t baseAddress) noexcept;

	~IUART() noexcept;

	void enable() noexcept;

	void disable() noexcept;

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
	UARTEnable(_baseAddress);
}

inline void
IUART::disable() noexcept
{
	UARTDisable(_baseAddress);
}

} // namespace uart
} // namespace tiva
