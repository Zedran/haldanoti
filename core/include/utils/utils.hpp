#pragma once

#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

namespace utils {

// Returns Color structure decoded from an HTML hex format. Allowed variations
// are "#rrggbb" and "#rrggbbaa". '#' is optional. Throws runtime_error
// if html_code has invalid format.
sf::Color decode_color(std::string html_code);

bool detect_collision(sf::FloatRect rect, sf::Vector2i point);

// Returns true if point is in contact with rect.
bool detect_collision(sf::FloatRect rect, sf::Vector2f point);

// Returns sf::Vector2f with rounded components. Fractions can cause a blur
// at the edges of drawable objects.
sf::Vector2f round(sf::Vector2f v);

} // namespace utils
