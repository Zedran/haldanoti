#include "gfx/Binding.hpp"

namespace ui {

Binding::~Binding() = default;

void Binding::invoke() {
    if (callback_) {
        callback_();
    }
    pressed_ = false;
}

bool Binding::is_pressed() const noexcept {
    return pressed_;
}

void Binding::press() noexcept {
    pressed_ = true;
}

void Binding::release() noexcept {
    pressed_ = false;
}

} // namespace ui
