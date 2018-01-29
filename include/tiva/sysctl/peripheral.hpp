#pragma once

#include <cstdint>
#include "driverlib/sysctl.h"

namespace tiva {
namespace sysctl {
	
class IPeripheral
{
public:
	IPeripheral(const IPeripheral& other) = delete;
	IPeripheral& operator=(const IPeripheral& other) = delete;
	
	IPeripheral(IPeripheral&&) = delete;
	IPeripheral& operator=(IPeripheral&& other) = delete;

protected:
	explicit IPeripheral(uint32_t peripheralId) noexcept
		:	_peripheralId(peripheralId)
	{
		enable();
	}

	~IPeripheral() noexcept
	{
		disable();
	}

private:
	void enable()
	{
		SysCtlPeripheralEnable(_peripheralId);
		while(!SysCtlPeripheralReady(_peripheralId));
	}

	void disable()
	{
		SysCtlPeripheralDisable(_peripheralId);
		while(SysCtlPeripheralReady(_peripheralId));
	}

	const std::uint32_t _peripheralId;
};

template<uint32_t _PeripheralId>
class Peripheral
	:	public IPeripheral
{
public:
	constexpr static auto PeripheralId = _PeripheralId;

	Peripheral() noexcept
		:	IPeripheral(PeripheralId)
	{}

	~Peripheral() = default;
};

} // namespace sysctl
} // namespace tiva

