// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <SFML/System/String.hpp>
#include <nlohmann/json.hpp>

#include "utils/json.hpp" // IWYU pragma: keep

namespace lang {

struct SecretRow {
    sf::String hint_unique;
    sf::String info_won;
    sf::String info_lost;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SecretRow, hint_unique, info_won, info_lost);

} // namespace lang
