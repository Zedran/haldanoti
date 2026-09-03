// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>

#include "config/Config.hpp"
#include "lang/Settings.hpp"
#include "theme/Settings.hpp"
#include "ui/Box.hpp"
#include "ui/Checkbox.hpp"

namespace app {

// Settings is a subpage of App that allows the player to specify their
// preferences such as the language of choice or whether the code may
// contain repeating elements.
class Settings : public ui::Box {
public:
    // A collection of states the Settings page can assume. The App class
    // uses these states to determine the behavior that the user requested.
    enum class State {
        // Keep displaying the Settings page.
        Running,

        // Save configuration and stop displaying Settings.
        SaveAndClose,

        // Stop displaying Settings without saving configuration.
        Close,
    };

    Settings(
        const sf::Font&         font,
        sf::Vector2f            size,
        lang::Settings          lang,
        theme::Settings         theme,
        std::vector<sf::String> lang_fnames
    );

    // Reads the values set by the player and returns them packed into
    // the Config struct.
    config::Config get_config() const noexcept;

    // Return the current State of the Settings.
    State get_state() const noexcept;

    // Set the values in the Settings page according to the received Config.
    void set_config(const config::Config& c);

    // Set a new State for the Settings.
    void set_state(State s) noexcept;

private:
    // Part of the total size of the Settings page taken by the options Box.
    static constexpr sf::Vector2f OPT_BOX_REL_SIZE{0.8f, 0.72f};

    // Part of the total size of the Settings page taken by the toolbar Box.
    static constexpr sf::Vector2f TOOLBAR_REL_SIZE{0.8f, 0.8f - OPT_BOX_REL_SIZE.y};

    // Dimensions of a single config option relative to the size
    // of the Settings page.
    static constexpr sf::Vector2f OPT_LINE_REL_SIZE{0.8f, 0.04f};

    // Button size relative to toolbar box height.
    static constexpr sf::Vector2f BUTTON_RELSIZE{0.9f, 0.5f};

    // Font size relative to the height of the button.
    static constexpr float FONT_REL_SIZE{0.4f};

    // Non-owning pointer to the Checkbox representing the unique elements
    // choice. Required for getting and setting its state.
    ui::Checkbox* cb_unique_elems_;

    // Non-owning pointer to the preferred language Selector.
    // Required for getting and setting its value.
    ui::Selector* sel_lang_;

    // Stores the current state of the Settings page.
    State state_;
};

} // namespace app
