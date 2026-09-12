// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <span>
#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace utils {

// Returns the number of distinct values found in code.
std::size_t count_distinct(std::span<const int> code);

// Returns Color structure decoded from an HTML hex format. Allowed variations
// are "#rrggbb" and "#rrggbbaa". '#' is optional. Throws runtime_error
// if html_code has invalid format.
sf::Color decode_color(std::string html_code);

// Returns true if point is in contact with rect.
bool detect_collision(sf::FloatRect rect, sf::Vector2i point);

// Returns true if point is in contact with rect.
bool detect_collision(sf::FloatRect rect, sf::Vector2f point);

// Returns sf::Vector2f with rounded components.
sf::Vector2f round(sf::Vector2f v);

} // namespace utils
