// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <optional>
#include <string>

#include <SFML/System/String.hpp>
#include <nlohmann/json.hpp>

namespace std {

// Converts JSON object to optional<string>. Empty string becomes nullopt.
void from_json(const nlohmann::json& j, std::optional<std::string>& v);

// Converts optional<string> to JSON object. nullopt becomes empty string.
void to_json(nlohmann::json& j, const std::optional<std::string> v);

} // namespace std

namespace sf {

// Converts JSON string to SFML String.
void from_json(const nlohmann::json& j, sf::String& v);

} // namespace sf
