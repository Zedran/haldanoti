// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

#include "app/UserInterface.hpp"
#include "app/Window.hpp"
#include "game/Game.hpp"
#include "lang/Lang.hpp"
#include "theme/Theme.hpp"

namespace app {

// Main class of the application.
class App {
public:
    App(
        sf::Vector2f   window_size,
        config::Config conf,
        lang::Lang     lang,
        theme::Theme   theme,
        sf::String     version
    );

    ~App();

    // Starts the application's main loop.
    void run();

private:
    // Logic engine.
    game::Game game_;

    // Application's frontend.
    UserInterface ui_;

    // Render target.
    Window window_;

    // Apply configuration options that can take effect without restarting
    // the application.
    void apply_config(const config::Config& c);

    // Causes the game loop to end.
    void close();

    // Sets the hints on the Board according to the user's preference.
    // Hint is a number of distinct elements in the secret code or nullopt,
    // in case hints are to be hidden.
    //
    // Calls related to this function need to be passed all the way down from
    // App to the SecretRow, because the former controls the logic engine and
    // config. The logic engine provides the secret code from which the hint
    // is derived and config determines whether the player wants hints.
    void configure_hints(const config::Config& c);

    // Resets logic engine and game display.
    void new_game();

    // Handles SFML events.
    void poll_events();

    // Gathers the state from the elements of the Settings page
    // and writes them into the config file.
    void save_config();

    // Game logic tick.
    void tick();
};

} // namespace app
