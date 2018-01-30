#pragma once

#include "tiva/sysctl/IPeripheral.hpp"

namespace tiva {
namespace gpio {

class IPort
	:	public sysctl::IPeripheral
{
public:

protected:
	explicit IPort(std::uint32_t peripheralId) noexcept;

	~IPort() noexcept = default;
};

inline
IPort::IPort(std::uint32_t peripheralId) noexcept
	:	sysctl::IPeripheral(peripheralId)
{}

} // namespace gpio
} // namespace tiva
