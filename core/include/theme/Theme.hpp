// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <SFML/Graphics/Color.hpp>

#include "theme/Board.hpp"
#include "theme/Settings.hpp"
#include "theme/Toolbar.hpp"
#include "ui/Label.hpp"

namespace theme {

// Top-level theme structure.
struct Theme {
    sf::Color bg;
    Board     board;
    ui::Label::Style message;
    Toolbar   toolbar;
    Settings  settings;
};

} // namespace theme
