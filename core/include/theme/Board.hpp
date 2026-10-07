// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <nlohmann/json.hpp>

#include "theme/GameRow.hpp"
#include "theme/SecretRow.hpp"
#include "ui/Box.hpp"
#include "utils/json.hpp" // IWYU pragma: keep

namespace theme {

struct Board {
    // Outer box of the Board.
    ui::Box::Style box;

    // Style shared by all game rows.
    GameRow game_row;

    // Style for the row holding the secret code.
    SecretRow secret_row;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    Board,
    box,
    game_row,
    secret_row
);

} // namespace theme
