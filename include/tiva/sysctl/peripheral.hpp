#pragma once

#include <cstdint>

#include "tiva/sysctl/system-control.hpp"

namespace tiva {
namespace sysctl {
	
template<uint32_t _PeripheralId>
class Peripheral
{
public:
	constexpr static auto PeripheralId = _PeripheralId;

	Peripheral(SystemControl& systemControl)
		:	_systemControl(systemControl)
	{
		_systemControl.enablePeripheral(*this);
	}

	~Peripheral()
	{
		_systemControl.disablePeripheral(*this);
	}

private:
	SystemControl& _systemControl;
};

} // namespace sysctl
} // namespace tiva

