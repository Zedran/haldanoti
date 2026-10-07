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

// Style of the Settings class.
struct Settings {
    // Background of the settings page.
    ui::Box::Style bg;

    // Style of the option box, drawn over background.
    ui::Box::Style box;

    // Style used by every Label on the settings page.
    ui::Label::Style label;

    // Style used by every Checkbox on the settings page.
    ui::Checkbox::Style checkbox;

    // Style used by every Selector on the settings page.
    ui::Selector::Style selector;

    // Style of the "Save" button.
    ui::Button::Style save;

    // Style of the "Cancel" button.
    ui::Button::Style cancel;
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
);

} // namespace theme
