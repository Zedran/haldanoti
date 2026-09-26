// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include "app/Window.hpp"
#include "utils/assets.hpp"
#include "utils/debug.hpp"

namespace app {

Window::Window(sf::Vector2f window_size, bool vsync)
    : sf::RenderWindow{sf::VideoMode{static_cast<sf::Vector2u>(window_size)}, "mm", sf::Style::Close} {
    dbg("screen_size = {{{:.0f}, {:.0f}}}", window_size.x, window_size.y);

    setIcon(utils::load_asset<sf::Image>("mm.png"));
    set_vsync(vsync);
}

Window::~Window() = default;

void Window::set_vsync(bool enabled) {
    dbg("VSync: {}", enabled);
    setVerticalSyncEnabled(enabled);
    setFramerateLimit(enabled ? FPS_UNLIM : FPS_LIMIT);
}

} // namespace app
