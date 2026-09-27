// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <SFML/Window/VideoMode.hpp>

#include "app/Window.hpp"
#include "utils/assets.hpp"
#include "utils/debug.hpp"
#include "utils/utils.hpp"

namespace app {

Window::Window(sf::Vector2f window_size, bool vsync)
    : sf::RenderWindow{sf::VideoMode{static_cast<sf::Vector2u>(window_size)}, "mm", sf::Style::Close} {
    dbg("screen_size = {{{:.0f}, {:.0f}}}", window_size.x, window_size.y);

    setIcon(utils::load_asset<sf::Image>("mm.png"));
    set_vsync(vsync);
}

Window::~Window() = default;

sf::Vector2f Window::default_size() noexcept {
    // Target aspect ratio.
    constexpr float ASPECT_RATIO{9.0f / 16.0f};

    // Height of the Window relative to the vertical dimension of the screen.
    constexpr float VERTICAL_SCALE{0.80f};

    const auto desktop = sf::VideoMode::getDesktopMode();

    const float win_h = static_cast<float>(desktop.size.y) * VERTICAL_SCALE;

    return utils::round({
        win_h * ASPECT_RATIO,
        win_h,
    });
}

void Window::set_vsync(bool enabled) {
    dbg("VSync: {}", enabled);
    setVerticalSyncEnabled(enabled);
    setFramerateLimit(enabled ? FPS_UNLIM : FPS_LIMIT);
}

} // namespace app
