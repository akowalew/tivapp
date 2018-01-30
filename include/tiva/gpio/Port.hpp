#pragma once

#include "tiva/gpio/IPort.hpp"

namespace tiva {
namespace gpio {

template<std::uint32_t PeripheralId, std::uint32_t _BaseAddress>
class Port
	:	public IPort
{
public:
	constexpr static auto BaseAddress = _BaseAddress;

	template<std::size_t _PinNumber, typename PinFunction>
	class Pin;

	Port() noexcept;

	~Port() noexcept = default;
};

template<std::uint32_t PeripheralId, std::uint32_t BaseAddress>
inline
Port<PeripheralId, BaseAddress>::Port() noexcept
	:	IPort(PeripheralId)
{}

} // namespace gpio
} // namespace tiva
