// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <cstddef>
#include <optional>
#include <span>

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>

#include "app/GameRow.hpp"
#include "app/SecretRow.hpp"
#include "lang/Board.hpp"
#include "theme/Board.hpp"
#include "ui/Box.hpp"

namespace app {

// Top-level container for the game display.
class Board final : public ui::Box {
public:
    // Size relative to outer container.
    static constexpr sf::Vector2f REL_SIZE{0.90f, 0.88f};

    Board(
        const sf::Font& font,
        sf::Vector2f    size,
        lang::Board     lang,
        theme::Board    theme,
        bool            code_chars,
        bool            fb_chars
    );

    ~Board();

    // Relays the setting to the static GameRow::allow_unique_only function
    // to set the evaluation strategy for the GameRow::all_set member function.
    // The parameter must be coherent with the game's unique_only setting.
    void allow_unique_only(bool v) noexcept;

    // Displays the secret code and the result. game::State::Running does not
    // signal the conclusion of the game, therefore attempting to set this
    // state through the end_game function will result in assertion error.
    void end_game(std::span<const int> good_code, game::State state);

    // Returns a mutable reference to the currently active GameRow.
    GameRow& get_active_row() const noexcept;

    // Returns true if currently active GameRow is the last available row.
    bool is_last_row() const noexcept;

    // Unlocks the next GameRow. Calling this function to progress past
    // the last row of the Board will cause assertion error.
    void next_row();

    // Resets the Board instance.
    void reset();

    // Relays settings to the SecretRow::set_hints member function, which
    // applies the hints config option. The hint parameter is a number of
    // distinct elements in the secret code. nullopt means that the unique_elems
    // option was set and hint should reflect that.
    void set_hints(bool enabled, std::optional<std::size_t> hint);

private:
    // Index of the currently active GameRow.
    std::size_t active_row_;

    // Stores non-owning pointers to GameRow instances.
    std::vector<GameRow*> game_rows_;

    // Holds a non-owning pointer to the SecretRow instance.
    SecretRow* secret_row_;
};

} // namespace app
