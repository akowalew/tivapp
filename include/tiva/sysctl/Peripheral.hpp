#pragma once

namespace tiva {
namespace sysctl {

template<uint32_t _PeripheralId>
class Peripheral
{
public:
	constexpr static auto PeripheralId = _PeripheralId;

};

} // namespace sysctl
} // namespace tiva

