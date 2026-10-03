// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <nlohmann/json.hpp>

#include "ui/Box.hpp"
#include "ui/Checkbox.hpp"
#include "ui/Label.hpp"
#include "ui/Selector.hpp"
#include "utils/json.hpp" // IWYU pragma: keep

namespace theme {

struct Settings {
    ui::Box::Style      bg;
    ui::Box::Style      box;
    ui::Label::Style    label;
    ui::Checkbox::Style checkbox;
    ui::Selector::Style selector;
    ui::Button::Style   save;
    ui::Button::Style   cancel;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    Settings,
    bg,
    box,
    label,
    checkbox,
    selector,
    save,
    cancel
)

} // namespace theme
