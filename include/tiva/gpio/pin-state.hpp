#pragma once

#include <cstdint>
#include "tiva/gpio/state.hpp"

namespace tiva {
namespace gpio {

template<typename _PinType>
struct PinState
{
	using PinType = _PinType;

	PinType& pin;
	State state;

	PinState(PinType& pin, State state) noexcept
		:	pin(pin),
			state(state)
	{}

	uint8_t getValue() const
	{
		return (static_cast<std::uint8_t>(state) << PinType::PinNumber);		
	}
};

} // namespace gpio
} // namespace tiva