#pragma once

#include <SFML/Graphics/Color.hpp>

#include "theme/Board.hpp"
#include "theme/Toolbar.hpp"

namespace theme {

// Top-level theme structure.
struct Theme {
    sf::Color bg;
    Board     board;
    Toolbar   toolbar;
};

} // namespace theme
