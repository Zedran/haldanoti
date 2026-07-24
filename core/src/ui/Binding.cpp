// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include "ui/Binding.hpp"

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
