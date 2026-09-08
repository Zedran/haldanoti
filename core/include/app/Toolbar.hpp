// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <functional>

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>

#include "lang/Toolbar.hpp"
#include "theme/Toolbar.hpp"
#include "ui/Box.hpp"

namespace app {

// User interface element that allows player to control top-level functions
// of the application (game reset, exit).
class Toolbar final : public ui::Box {
    // Button size relative to Toolbar's height.
    static constexpr sf::Vector2f BUTTON_RELSIZE{1.5f, 0.8f};

    // Font size relative to the height of the button.
    static constexpr float FONT_REL_SIZE{0.4f};

public:
    // Size relative to outer container.
    static constexpr sf::Vector2f REL_SIZE{1.0f, 0.065f};

    Toolbar(
        const sf::Font&       font,
        sf::Vector2f          size,
        lang::Toolbar         lang,
        theme::Toolbar        theme,
        std::function<void()> new_game_func,
        std::function<void()> settings_func,
        std::function<void()> exit_func
    );

    ~Toolbar();
};

} // namespace app
