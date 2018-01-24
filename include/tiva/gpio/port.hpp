#pragma once

#include <utility>

#include "tiva/sysctl/peripheral.hpp"
#include "tiva/gpio/pin.hpp"
#include "tiva/sysctl/system-control.hpp"

#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"

namespace tiva {
namespace gpio {

template<uint32_t PeripheralId, uint32_t _BaseAddress>
struct Port
	:	public sysctl::Peripheral<PeripheralId>
{
	constexpr static auto BaseAddress = _BaseAddress;
	using PeripheralType = sysctl::Peripheral<PeripheralId>;

	using PeripheralType::Peripheral;
};

struct PortE
	:	public Port<SYSCTL_PERIPH_GPIOE, GPIO_PORTE_BASE>
{
	using PortType = Port<SYSCTL_PERIPH_GPIOE, GPIO_PORTE_BASE>;
	using PortType::Port;
};

} // namespace gpio
} // namespace tiva

	// template<size_t PinNumber>
	// Pin<PinNumber, ThisPort> getPin()
	// {
	// 	return Pin<PinNumber, ThisPort>(*this);
	// }

	// template<typename PinType>
	// void setAsOutput(PinType& pin)
	// {
	// 	IPort::setAsOutput(PinType::PinMask);
	// }

	// template<typename PinType, typename... Rest>
	// void setAsOutput(PinType& pin, Rest... rest)
	// {
	// 	const auto pinsMask = getPinsMask(pin, rest...);
	// 	IPort::setAsOutput(pinsMask);
	// }

	// template<typename PinType>
	// void read() const
	// {
	// 	IPort::
	// }

	// template<typename PinState>
	// void write(PinState pinState)
	// {
	// 	const auto [mask, value] = parsePinsStates(pinState);
	// 	IPort::write(mask, value);
	// }

	// template<typename PinState, typename... Rest>
	// void write(PinState pinState, Rest... rest)
	// {
	// 	const auto [mask, value] = parsePinsStates(pinState, rest...);
	// 	IPort::write(mask, value);
	// }

// private:
	// template<typename PinType>
	// uint8_t getPinsMask(PinType& pinType)
	// {
	// 	return PinType::PinMask;
	// }

	// template<typename PinType, typename... Rest>
	// uint8_t getPinsMask(PinType& pinType, Rest... rest)
	// {
	// 	return PinType::PinMask | getPinsMask(rest...);
	// }

	// template<typename PinState>
	// std::pair<uint8_t, uint8_t> parsePinsStates(PinState pinState)
	// {
	// 	using PinType = typename PinState::PinType;
	// 	const auto mask = PinType::PinMask;
	// 	const auto value = pinState.getValue();
	// 	return std::make_pair(mask, value);
	// }

	// template<typename PinState, typename... Rest>
	// std::pair<uint8_t, uint8_t> parsePinsStates(PinState pinState, Rest... rest)
	// {
	// 	using PinType = typename PinState::PinType;
	// 	auto [mask, value] = parsePinsStates(rest...);
	// 	mask |= PinType::PinMask;
	// 	value |= pinState.getValue();
	// 	return std::make_pair(mask, value);
	// }