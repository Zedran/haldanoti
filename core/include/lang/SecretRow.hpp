// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <SFML/System/String.hpp>

namespace lang {

struct SecretRow {
    sf::String info_running;
    sf::String info_won;
    sf::String info_lost;
};

} // namespace lang
