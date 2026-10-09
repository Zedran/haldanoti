// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <catch2/catch_test_macros.hpp>

#include <array>
#include <cstddef>
#include <optional>
#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

#include "utils/utils.hpp"

TEST_CASE("count_distinct") {
    constexpr std::size_t T = 4;

    struct test_data {
        std::array<int, T> code;
        std::size_t        distinct;
    };

    constexpr test_data test_cases[]{
        {{1, 2, 3, 4}, 4},
        {{1, 1, 3, 4}, 3},
        {{1, 1, 1, 4}, 2},
        {{1, 1, 1, 1}, 1},
        {{1, 2, 1, 2}, 2},
    };

    for (const auto& c : test_cases) {
        REQUIRE(utils::count_distinct(c.code) == c.distinct);
    }
}

TEST_CASE("decode_color") {
    struct test_data {
        std::string              input;
        std::optional<sf::Color> expected{};

        bool good_case() const noexcept {
            return expected.has_value();
        }
    };

    const test_data test_cases[]{
        {"#000000", sf::Color{0x000000ff}},   // #RGB
        {"ffffff", sf::Color{0xffffffff}},    // RGB
        {"#00000000", sf::Color{0x00000000}}, // #RGBA
        {"ffffff50", sf::Color{0xffffff50}},  // RGBA
        {""},                                 // Empty string
        {"#12345"},                           // Too short for #RGB
        {"12345"},                            // Too short for RGB
        {"#1234567"},                         // Too short for #RGBA
        {"1234567"},                          // Too short for RGBA
        {"#123456789"},                       // Too long for #RGBA
        {"123456789"},                        // Too long for RGBA
        {"#hello"},                           // Invalid characters
        {"hello"},                            // Invalid characters
    };

    for (const auto& c : test_cases) {
        CAPTURE(c.input);

        if (c.good_case()) {
            const sf::Color out = utils::decode_color(c.input);
            REQUIRE(out == *c.expected);
        } else {
            REQUIRE_THROWS(utils::decode_color(c.input));
        }
    }
}

TEST_CASE("detect_collision") {
    struct test_data {
        sf::Vector2f point;
        bool         expected;
    };

    constexpr sf::FloatRect rect{{0, 0}, {50, 50}};

    const test_data test_cases[]{
        {{0, 0}, true},
        {{49, 49}, true},
        {{25, 25}, true},
        {{-1, -1}, false},
        {{25, -5}, false},
        {{-5, 25}, false},
        {{50, 50}, false},
    };

    for (const auto& c : test_cases) {
        CAPTURE(c.point.x, c.point.y);

        const bool out = utils::detect_collision(rect, c.point);
        REQUIRE(out == c.expected);
    }
}
