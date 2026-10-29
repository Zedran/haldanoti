// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <SFML/System/String.hpp>
#include <nlohmann/json.hpp>

#include "utils/json.hpp" // IWYU pragma: keep

namespace lang {

struct Message {
    sf::String restart_required;
    sf::String starting_new_game;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Message, restart_required, starting_new_game);

} // namespace lang
