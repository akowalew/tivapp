#pragma once

#include "tiva/uart/IUART.hpp"

namespace tiva {
namespace uart {

template<uint32_t PeripheralId, uint32_t BaseAddress,
	typename RxPinType, typename TxPinType>
class UART
	:	public IUART
{
public:
	UART(RxPinType& rxPin, TxPinType& txPin) noexcept;

	~UART() noexcept = default;
};

template<std::uint32_t PeripheralId, std::uint32_t BaseAddress,
	typename RxPinType, typename TxPinType>
inline
UART<PeripheralId, BaseAddress, RxPinType, TxPinType>
	::UART(RxPinType& rxPin, TxPinType& txPin) noexcept
	:	IUART(PeripheralId, BaseAddress)
{
	static_cast<void>(rxPin);
	static_cast<void>(txPin);
}

} // namespace uart
} // namespace tiva
