// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include "theme/CodeButton.hpp"
#include "theme/GameRow.hpp"
#include "theme/SecretRow.hpp"
#include "ui/Box.hpp"

namespace theme {

struct Board {
    // Outer box of the Board.
    ui::Box::Style box;

    // theme::Board is the owner of styles for CodeButton.
    // theme::GameRow and theme::SecretRow hold a pointer to it.
    // This arrangement prevents duplication of vector containing
    // element styles.
    CodeButton code_button;

    // Style shared by all game rows.
    GameRow game_row;

    // Style for the row holding the secret code.
    SecretRow secret_row;
};

} // namespace theme
