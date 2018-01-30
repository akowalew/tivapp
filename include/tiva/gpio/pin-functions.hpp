#pragma once

namespace tiva {
namespace gpio {

struct PinFunctionBase {};
struct InputFunction : public PinFunctionBase {};
struct OutputFunction : public PinFunctionBase {};
struct InputOutputFunction : public PinFunctionBase {};
struct HardwareFunction : public PinFunctionBase {};

} // namespace gpio
} // namespace tiva
