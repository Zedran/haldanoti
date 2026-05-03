#pragma once

#include <string>

#include <SFML/Graphics/Color.hpp>

namespace utils {

// Returns Color structure decoded from an HTML hex format. Allowed variations
// are "#rrggbb" and "#rrggbbaa". '#' is optional. Throws runtime_error
// if html_code has invalid format.
sf::Color decode_color(std::string html_code);

} // namespace utils
