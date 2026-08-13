// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <SFML/System/String.hpp>
#include <nlohmann/json.hpp>

#include "utils/json.hpp" // IWYU pragma: keep

namespace lang {

struct Toolbar {
    sf::String new_game;
    sf::String exit;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Toolbar, new_game, exit);

} // namespace lang
