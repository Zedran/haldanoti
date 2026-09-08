// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include "app/Toolbar.hpp"
#include "ui/Button.hpp"

namespace app {

Toolbar::Toolbar(
    const sf::Font&       font,
    sf::Vector2f          size,
    lang::Toolbar         lang,
    theme::Toolbar        theme,
    std::function<void()> new_game_func,
    std::function<void()> settings_func,
    std::function<void()> exit_func
) : ui::Box{size, theme.box, ui::Layout::Type::RowLayout} {
    const unsigned int font_size = static_cast<unsigned int>(size.y * FONT_REL_SIZE);

    add_component<ui::Button>(
        font,
        sf::Vector2f{size.y * BUTTON_RELSIZE.x, size.y * BUTTON_RELSIZE.y},
        theme.new_game,
        lang.new_game,
        font_size
    )
        .bind(sf::Mouse::Button::Left, new_game_func);

    add_component<ui::Button>(
        font,
        sf::Vector2f{size.y * BUTTON_RELSIZE.x, size.y * BUTTON_RELSIZE.y},
        theme.settings,
        lang.settings,
        font_size
    )
        .bind(sf::Mouse::Button::Left, settings_func);

    add_component<ui::Button>(
        font,
        sf::Vector2f{size.y * BUTTON_RELSIZE.x, size.y * BUTTON_RELSIZE.y},
        theme.exit,
        lang.exit,
        font_size
    )
        .bind(sf::Mouse::Button::Left, exit_func);
}

Toolbar::~Toolbar() = default;

} // namespace app
