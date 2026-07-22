#pragma once

#include "ui/Box.hpp"
#include "ui/Button.hpp"

namespace theme {

struct Toolbar {
    // Outer box.
    ui::Box::Style box;

    // New Game button.
    ui::Button::Style new_game;

    // Exit button.
    ui::Button::Style exit;
};

} // namespace theme
