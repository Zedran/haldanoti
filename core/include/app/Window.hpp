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
    Window(sf::Vector2f window_size, sf::Color bg, bool vsync);

    ~Window();

    // Clears window according to the selected background color.
    // Exposed in the header to allow inlining. Avoiding the name
    // 'clear' for distinction from the RenderWindow::clear called
    // with default argument.
    void draw_bg() {
        clear(bg_);
    }

    // Enables or disables VSync and sets the framerate limit accordingly.
    void set_vsync(bool enabled);

private:
    // Framerate limit when vertical sync is disabled.
    static constexpr unsigned int FPS_LIMIT = 60;

    // High framerate limit that does not collide with vertical sync.
    static constexpr unsigned int FPS_UNLIM = std::numeric_limits<unsigned int>::max();

    // Window background color.
    sf::Color bg_;
};

} // namespace app
