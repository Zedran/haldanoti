// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <cstddef>
#include <optional>

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "app/Board.hpp"
#include "app/Message.hpp"
#include "app/Settings.hpp"
#include "app/Toolbar.hpp"
#include "app/Window.hpp"
#include "lang/Lang.hpp"
#include "theme/Theme.hpp"

namespace app {

// UserInterface contains Widgets that the player interacts with.
class UserInterface {
public:
    // Used by the App class to determine actions requested by the player.
    enum class Signal {
        // No action required.
        None,

        // New game requested.
        NewGame,

        // Save current configuration.
        SaveConfig,

        // Close the game.
        Exit,
    };

    UserInterface(
        sf::Vector2f   window_size,
        config::Config conf,
        lang::Lang     lang,
        theme::Theme   theme,
        sf::String     version
    );

    ~UserInterface();

    // Calls the draw member function of every sf::Drawable
    // and displays the resulting frame.
    void draw(Window& window);

    // Returns currently stored Signal and sets current Signal to None.
    Signal emit_signal() noexcept;

    // Returns a reference to Board instance.
    Board& get_board() noexcept;

    // Returns a reference to Settings instance.
    Settings& get_settings() noexcept;

    // Relays the event to the controlled Widgets.
    void handle_event(const sf::Event& event);

    // Reset the state of the UI to prepare it for a new game.
    void reset();

    // Relays the number of distinct elements in secret code
    // to the Board::set_hint function. nullopt disables hints.
    void set_hints(std::optional<std::size_t> hint);

    void show_message(Message::Content msg);

    // Updates the UI state on every frame.
    void update();

private:
    // Indicates which scene should be displayed.
    enum class Scene {
        Game,
        Settings,
    };

    // Font used by the UI.
    sf::Font font_;

    // Window background color.
    sf::Color bg_;

    // Game display.
    Board board_;

    Message message_;

    // Currently displayed scene.
    Scene scene_;

    // Settings page.
    Settings settings_;

    // Stores the current Signal value until emit_signal is called.
    Signal signal_;

    Toolbar toolbar_;

    // Sets the current scene, allowing the App to transition between the game
    // and subpages.
    void set_scene(Scene scene) noexcept;

    void set_signal(Signal signal) noexcept;
};

} // namespace app
