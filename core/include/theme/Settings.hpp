// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include "ui/Box.hpp"
#include "ui/Checkbox.hpp"
#include "ui/Selector.hpp"

namespace theme {

struct Settings {
    ui::Box::Style      box;
    ui::Checkbox::Style checkbox;
    ui::Selector::Style selector;
    ui::Button::Style   save;
    ui::Button::Style   cancel;
};

} // namespace theme
