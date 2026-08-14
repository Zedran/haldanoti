// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "app/Board.hpp"
#include "app/Toolbar.hpp"
#include "game/Game.hpp"
#include "lang/Lang.hpp"
#include "theme/Theme.hpp"

namespace app {

// Main class of the application.
class App {
public:
    App(
        const sf::Font& font,
        sf::Image       icon,
        sf::Vector2f    window_size,
        bool            unique_elems,
        lang::Lang      lang,
        theme::Theme    theme
    );

    ~App();

    // Starts the application's main loop.
    int run();

private:
    // Window background color.
    sf::Color bg_;

    // Game display.
    Board board_;

    // Logic engine.
    game::Game game_;

    Toolbar toolbar_;

    // Render target.
    sf::RenderWindow window_;

    // Function for the exit button.
    void close();

    // Calls the draw member function for every sf::Drawable
    // and displays the resulting frame.
    void draw();

    // Resets logic engine and game display.
    void new_game();

    // Handles SFML events.
    void poll_events();

    // Game logic tick.
    void tick();
};

} // namespace app
