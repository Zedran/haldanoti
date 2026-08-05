// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <span>
#include <vector>

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>

#include "app/CodeButton.hpp"
#include "game/Row.hpp"
#include "game/State.hpp"
#include "lang/SecretRow.hpp"
#include "theme/SecretRow.hpp"
#include "ui/Box.hpp"
#include "ui/Label.hpp"

namespace app {

// Specialized Box that displays the correct code and the outcome information
// upon the game's conclusion.
class SecretRow final : public ui::Box {
public:
    // Size relative to outer container.
    static constexpr sf::Vector2f REL_SIZE{1.0f, 0.077f};

    SecretRow(const sf::Font& font, sf::Vector2f size, lang::SecretRow lang, theme::SecretRow theme);

    ~SecretRow();

    // Displays the code until reset.
    void display_code(std::span<const int, game::Row::ROW_LEN> code);

    // Displays the selected info indefinitely.
    void display_info(game::State state) noexcept;

    // Clears the displayed code and info.
    void reset();

private:
    // Size of the code box relative to the dimensions of the SecretRow's
    // container.
    static constexpr sf::Vector2f CODE_BOX_REL_SIZE{0.46f, 1.0f};

    // Size of the info box relative to the dimensions of the SecretRow's
    // container.
    static constexpr sf::Vector2f INFO_BOX_REL_SIZE{0.54f, 1.0f};

    // Font size relative to the height of the info box.
    static constexpr float INFO_FONT_REL_SIZE{0.5f};

    // Holds non-owning pointers to CodeButton instances used to display secret
    // code.
    std::vector<CodeButton*> code_buttons_;

    // Holds non-owning pointer to the info Label.
    ui::Label* info_;

    // Contains strings that can be set to notification label.
    lang::SecretRow lang_;

    // Stores styling information required by different notifications displayed
    // in the info box.
    theme::SecretRow theme_;
};

} // namespace app
