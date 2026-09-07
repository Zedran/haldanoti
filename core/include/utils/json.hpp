// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <SFML/System/String.hpp>
#include <nlohmann/json.hpp>

namespace sf {

// Converts JSON string to SFML String.
void from_json(const nlohmann::json& j, sf::String& v);

} // namespace sf
