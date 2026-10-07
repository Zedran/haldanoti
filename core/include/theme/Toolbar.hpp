// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <nlohmann/json.hpp>

#include "ui/Box.hpp"
#include "ui/Button.hpp"
#include "utils/json.hpp" // IWYU pragma: keep

namespace theme {

struct Toolbar {
    // Outer box.
    ui::Box::Style box;

    // New Game button.
    ui::Button::Style new_game;

    // Settings page.
    ui::Button::Style settings;

    // Exit button.
    ui::Button::Style exit;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    Toolbar,
    box,
    new_game,
    settings,
    exit
);

} // namespace theme
