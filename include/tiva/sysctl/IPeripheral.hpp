#pragma once

#include <cstdint>
#include "driverlib/sysctl.h"

namespace tiva {
namespace sysctl {

class IPeripheral
{
public:
	IPeripheral(const IPeripheral& other) noexcept = delete;
	IPeripheral& operator=(const IPeripheral& other) noexcept = delete;

	IPeripheral(IPeripheral&&) noexcept = delete;
	IPeripheral& operator=(IPeripheral&& other) noexcept = delete;

protected:
	explicit IPeripheral(uint32_t peripheralId) noexcept;

	~IPeripheral() noexcept;

private:
	void enable() noexcept;

	void disable() noexcept;

	const std::uint32_t _peripheralId;
};

inline
IPeripheral::IPeripheral(uint32_t peripheralId) noexcept
	:	_peripheralId(peripheralId)
{
	enable();
}

inline
IPeripheral::~IPeripheral() noexcept
{
	disable();
}

inline void
IPeripheral::enable() noexcept
{
	SysCtlPeripheralEnable(_peripheralId);
	while(!SysCtlPeripheralReady(_peripheralId));
}

inline void
IPeripheral::disable() noexcept
{
	SysCtlPeripheralDisable(_peripheralId);
	while(SysCtlPeripheralReady(_peripheralId));
}

} // namespace sysctl
} // namespace tiva
