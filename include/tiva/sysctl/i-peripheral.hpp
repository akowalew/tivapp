#pragma once

#include <cstdint>

#include "driverlib/sysctl.h"
#include "driverlib/rom.h"

namespace tiva {
namespace sysctl {
	
class IPeripheral
{
public:
	IPeripheral(std::uint32_t id)
		:	_id(id)
	{
		enablePeripheral();
	}

	~IPeripheral()
	{
		disablePeripheral();
	}

	std::uint32_t getId() const
	{
		return _id;
	}

private:
	void enablePeripheral()
	{
		ROM_SysCtlPeripheralEnable(_id);
		while(!ROM_SysCtlPeripheralReady(_id))
		{}
	}	

	void disablePeripheral()
	{
		ROM_SysCtlPeripheralDisable(_id);
		while(ROM_SysCtlPeripheralReady(_id))
		{}
	}

	const std::uint32_t _id;
};

} // namespace sysctl
} // namespace tiva