// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

#include "utils/utils.hpp"

namespace utils {

std::size_t count_distinct(std::span<const int> code) {
    std::vector<int> seen;
    seen.reserve(code.size());

    std::size_t distinct{};

    for (const auto& e : code) {
        if (std::find(seen.begin(), seen.end(), e) == seen.end()) {
            distinct++;
            seen.push_back(e);
        }
    }

    return distinct;
}

sf::Color decode_color(std::string html_code) {
    constexpr std::size_t SIZE_RGB  = 6;
    constexpr std::size_t SIZE_RGBA = 8;
    constexpr const char* ALPHA_100 = "ff";

    const std::size_t first_index = (html_code.front() == '#') ? 1 : 0;

    switch (html_code.size() - first_index) {
    case SIZE_RGB:  html_code += ALPHA_100; break;
    case SIZE_RGBA: break;
    default:        throw std::runtime_error{"invalid color code \"" + html_code + '"'};
    }

    const unsigned long long hex = std::stoull(html_code.substr(first_index), nullptr, 16);
    return sf::Color{static_cast<std::uint32_t>(hex)};
}

bool detect_collision(sf::FloatRect rect, sf::Vector2i point) {
    return detect_collision(rect, static_cast<sf::Vector2f>(point));
}

bool detect_collision(sf::FloatRect rect, sf::Vector2f point) {
    return rect.contains(point);
}

sf::Vector2f round(sf::Vector2f v) {
    return {std::round(v.x), std::round(v.y)};
}

} // namespace utils
