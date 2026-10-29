// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/String.hpp>
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
        std::vector<sf::String> lang_fnames,
        std::vector<sf::String> theme_fnames,
        sf::String              version
    );

    // Returns true if conf differs from the reference Config struct. This
    // function can be used to determine whether settings were modified
    // since the last call to set_config or set_ref_config.
    bool config_differs(const config::Config& c) const noexcept;

    // Returns true if the game needs to be reset in order for the new settings
    // to take effect.
    bool game_reset_required(const config::Config& c) const noexcept;

    // Reads the values set by the player and returns them packed into
    // the Config struct.
    config::Config get_config() const noexcept;

    // Provides a view into the reference Config - Config that is currently
    // in effect.
    const config::Config& get_ref_config() const noexcept;

    // Return the current State of the Settings.
    State get_state() const noexcept;

    // Due to opaque design of ui::Box, some settings (e.g. language)
    // cannot be applied after the initialization of all elements.
    // This function returns true if these settings were changed.
    bool restart_required(const config::Config& c) const noexcept;

    // Sets the values in the Settings page according to the received Config
    // and updates the internal reference Config.
    void set_config(const config::Config& c);

    // Set c as the new reference for the config_differs function.
    void set_ref_config(const config::Config& c) noexcept;

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
    static constexpr sf::Vector2f BUTTON_RELSIZE{1.125f, 0.6f};

    // Font size relative to the height of the button.
    static constexpr float FONT_REL_SIZE{0.3f};

    // Dimensions of the version Label relative to the size
    // of the Settings page.
    static constexpr sf::Vector2f VERSION_RELSIZE{0.8f, 0.016f};

    // Non-owning pointer to the language Selector. Required for getting
    // and setting its value.
    ui::Selector* sel_lang_;

    // Non-owning pointer to the Checkbox representing the code characters
    // option. Required for getting and setting its state.
    ui::Checkbox* cb_code_chars_;

    // Non-owning pointer to the Checkbox representing the feedback characters
    // option. Required for getting and setting its state.
    ui::Checkbox* cb_fb_chars_;

    // Non-owning pointer to the Checkbox representing the hints option.
    // Required for getting and setting its state.
    ui::Checkbox* cb_hints_;

    // Non-owning pointer to the code length Selector. Required for getting
    // and setting its value.
    ui::Selector* sel_code_len_;

    // Non-owning pointer to the Checkbox representing the unique elements
    // option. Required for getting and setting its state.
    ui::Checkbox* cb_unique_elems_;

    // Non-owning pointer to the Checkbox representing the vsync option.
    // Required for getting and setting its state.
    ui::Checkbox* cb_vsync_;

    // Non-owning pointer to the theme Selector. Required for getting
    // and setting its value.
    ui::Selector* sel_theme_;

    // Config used as a reference to determine whether the settings were changed
    // between saves.
    config::Config ref_config_;

    // Stores the current state of the Settings page.
    State state_;

    // Resets the display state. Called if the cancel Button is pressed.
    void reset();
};

} // namespace app
