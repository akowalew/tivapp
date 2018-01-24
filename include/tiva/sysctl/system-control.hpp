#pragma once

#include <type_traits>

#include <cstdio>
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"

#include "tiva/sysctl/peripheral.hpp"

namespace tiva {
namespace sysctl {
	
class SystemControl
{
public:
	template<typename PeripheralType>
	void enablePeripheral(const PeripheralType& peripheral)
	{
		constexpr static auto PeripheralId = PeripheralType::PeripheralId;

		// static_cast<void>(peripheral);
		SysCtlPeripheralEnable(PeripheralId);
		while(!SysCtlPeripheralReady(PeripheralId))
		{
		}
	}

	template<typename PeripheralType>
	void disablePeripheral(const PeripheralType& peripheral)
	{
		constexpr static auto PeripheralId = PeripheralType::PeripheralId;

		// static_cast<void>(peripheral);
		SysCtlPeripheralDisable(PeripheralId);
		while(SysCtlPeripheralReady(PeripheralId))
		{
		}
	}
};

} // namespace sysctl
} // namespace tiva


	// void enable()
	// {
	// 	SysCtlPeripheralEnable(PeripheralId);
	// }

	// void disable()
	// {
	// 	SysCtlPeripheralDisable(PeripheralId);
	// }
	// void powerOn()
	// {
	// 	ROM_SysCtlPeripheralPowerOn(PeripheralId);
	// }

	// void powerOff()
	// {
	// 	ROM_SysCtlPeripheralPowerOff(PeripheralId);
	// }

	// bool ready()
	// {
	// 	return ROM_SysCtlPeripheralReady(PeripheralId);
	// }

	// void reset()
	// {
	// 	ROM_SysCtlPeripheralReset(PeripheralId);
	// }

	// void sleepEnable()
	// {
	// 	ROM_SysCtlPeripheralSleepEnable(PeripheralId);
	// }

	// void sleepDisable()
	// {
	// 	ROM_SysCtlPeripheralSleepDisable(PeripheralId);
	// }