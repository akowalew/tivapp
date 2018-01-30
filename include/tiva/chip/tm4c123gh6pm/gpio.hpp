#pragma once

namespace gpio {

struct PortE
	:	public Port<SYSCTL_PERIPH_GPIOE, GPIO_PORTE_BASE>
{};

} // namespace gpio
