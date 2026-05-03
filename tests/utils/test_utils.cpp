#include <catch2/catch_test_macros.hpp>

#include <string>
#include <variant>

#include <SFML/Graphics/Color.hpp>

#include "utils/utils.hpp"

TEST_CASE("decode_color") {
    struct test_data {
        std::string                   input;
        std::variant<sf::Color, bool> expected;

        bool good_case() const noexcept {
            return std::holds_alternative<sf::Color>(expected);
        }
    };

    const test_data test_cases[]{
        {"#000000", sf::Color{0x0, 0x0, 0x0, 0xff}},     // #RGB
        {"ffffff", sf::Color{0xff, 0xff, 0xff, 0xff}},   // RGB
        {"#00000000", sf::Color{0x0, 0x0, 0x0, 0x00}},   // #RGBA
        {"ffffff50", sf::Color{0xff, 0xff, 0xff, 0x50}}, // RGBA
        {"", true},                                      // Empty string
        {"#12345", true},                                // Too short for #RGB
        {"12345", true},                                 // Too short for RGB
        {"#1234567", true},                              // Too short for #RGBA
        {"1234567", true},                               // Too short for RGBA
        {"#123456789", true},                            // Too long for #RGBA
        {"123456789", true},                             // Too long for RGBA
        {"#hello", true},                                // Invalid characters
        {"hello", true},                                 // Invalid characters
    };

    for (const auto& c : test_cases) {
        CAPTURE(c.input);

        if (c.good_case()) {
            const sf::Color out = utils::decode_color(c.input);
            REQUIRE(out == std::get<sf::Color>(c.expected));
        } else {
            REQUIRE_THROWS(utils::decode_color(c.input));
        }
    }
}
