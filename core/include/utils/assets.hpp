// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <initializer_list>
#include <stdexcept>
#include <string_view>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Exception.hpp>

namespace utils {

// Iterates over the list of possible asset file locations and initializes
// T using the first found file. Throws runtime_error if no file was found.
template <typename T>
    requires std::is_same_v<T, sf::Font> || std::is_same_v<T, sf::Image>
T load_asset(std::initializer_list<std::string_view> paths) {
    for (const auto& p : paths) {
        try {
            if constexpr (std::is_same_v<T, sf::Font>) {
                return sf::Font{p};
            } else if constexpr (std::is_same_v<T, sf::Image>) {
                sf::Image img;
                if (img.loadFromFile(p)) {
                    return img;
                }
            }
        } catch (const sf::Exception&) {
        }
    }
    throw std::runtime_error{"unable to load asset"};
}

} // namespace utils
