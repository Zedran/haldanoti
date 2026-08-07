// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <nlohmann/json.hpp>

#include "lang/GameRow.hpp"
#include "lang/SecretRow.hpp"

namespace lang {

struct Board {
    GameRow   game_row;
    SecretRow secret_row;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Board, game_row, secret_row);

} // namespace lang
