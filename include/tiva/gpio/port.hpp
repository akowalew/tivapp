#pragma once

#include <utility>

#include "tiva/sysctl/peripheral.hpp"
// #include "tiva/gpio/pin.hpp"

#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"

namespace tiva {
namespace gpio {

class IPort
	:	public sysctl::IPeripheral
{
public:

protected:
	explicit IPort(std::uint32_t peripheralId) noexcept
		:	sysctl::IPeripheral(peripheralId)
	{}

	~IPort() = default;

private:

};

template<uint32_t PeripheralId, uint32_t _BaseAddress>
class Port
	:	public IPort
{
public:
	constexpr static auto BaseAddress = _BaseAddress;
	
	Port() noexcept
		:	IPort(PeripheralId)
	{}

	~Port() noexcept = default;

	template<size_t _PinNumber, typename PinFunction>
	class Pin;
};

struct PortE
	:	public Port<SYSCTL_PERIPH_GPIOE, GPIO_PORTE_BASE>
{
	// using PortType = Port<SYSCTL_PERIPH_GPIOE, GPIO_PORTE_BASE>;
	// using PortType::Port;
};

} // namespace gpio
} // namespace tiva
