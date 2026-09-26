// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <limits>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

namespace app {

// Applies a set of application-specific modifications to sf::RenderWindow.
class Window : public sf::RenderWindow {
public:
    Window(sf::Vector2f window_size, bool vsync);

    ~Window();

    // Enables or disables VSync and sets the framerate limit accordingly.
    void set_vsync(bool enabled);

private:
    // Framerate limit when vertical sync is disabled.
    static constexpr unsigned int FPS_LIMIT = 60;

    // High framerate limit that does not collide with vertical sync.
    static constexpr unsigned int FPS_UNLIM = std::numeric_limits<unsigned int>::max();
};

} // namespace app
