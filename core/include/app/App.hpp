// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <limits>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

#include "app/Board.hpp"
#include "app/Message.hpp"
#include "app/Settings.hpp"
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
        sf::Vector2f    window_size,
        config::Config  conf,
        lang::Lang      lang,
        theme::Theme    theme
    );

    ~App();

    // Starts the application's main loop.
    void run();

private:
    // Indicates which scene should be displayed.
    enum class Scene {
        Game,
        Settings,
    };

    // Framerate limit when vertical sync is disabled.
    static constexpr unsigned int FPS_LIMIT = 60;

    // High framerate limit that does not collide with vertical sync.
    static constexpr unsigned int FPS_UNLIM = std::numeric_limits<unsigned int>::max();

    // Window background color.
    sf::Color bg_;

    // Game display.
    Board board_;

    // Logic engine.
    game::Game game_;

    Message message_;

    // Currently displayed scene.
    Scene scene_;

    // Settings page.
    Settings settings_;

    Toolbar toolbar_;

    // Render target.
    sf::RenderWindow window_;

    // Apply configuration options that can take effect without restarting
    // the application.
    void apply_config(const config::Config& c);

    // Function for the exit button.
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

    // Calls the draw member function for every sf::Drawable
    // and displays the resulting frame.
    void draw();

    // Resets logic engine and game display.
    void new_game();

    // Handles SFML events.
    void poll_events();

    // Gathers the state from the elements of the Settings page
    // and writes them into the config file.
    void save_config();

    // Sets the current scene, allowing the App to transition between the game
    // and subpages.
    void set_scene(Scene scene) noexcept;

    // Enables or disables VSync and sets the framerate limit accordingly.
    void set_vsync(bool enabled);

    // Game logic tick.
    void tick();
};

} // namespace app
