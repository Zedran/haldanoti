// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <cstddef>
#include <optional>
#include <span>
#include <vector>

#include "game/Row.hpp"
#include "game/State.hpp"
#include "utils/Source.hpp"

namespace game {

// Logic engine of the game.
class Game {
public:
    // Number of rows, each representing one attempt at guessing the code.
    static constexpr std::size_t NUM_ROWS = 12;

    // The lowest number that can be assigned to the code field.
    static constexpr int SCORE_MIN = 1;

    // The highest number that can be assigned to the code field.
    static constexpr int SCORE_MAX = 8;

    // Number of unique code elements.
    static constexpr int NUM_UNIQUE_ELEMS = SCORE_MAX - SCORE_MIN + 1;

    // Constructs a new instance of the Game with secret code of length
    // code_len. Optionally, a custom seed for the random number generator
    // can be provided.
    Game(std::size_t code_len, bool unique_elems, std::optional<unsigned long> seed = std::nullopt);

    // Prevents integral type confusion in mistaken call Game{code_len, seed}.
    template <std::integral T>
    Game(T, T) = delete;

    // Prevents integral type confusion in call Game{unique_elems, seed}.
    // It was correct when constructor was defined as Game(unique_elems, seed),
    // now it can lead to mistakes if overloads are not explicitly removed.
    template <std::integral T>
    Game(bool, T) = delete;

    ~Game();

    // Returns a const reference to the currently active row.
    const Row& active_row() const noexcept;

    // Returns the number of currently active row.
    std::size_t active_row_num() const noexcept;

    // Progresses to the next row. Game cannot be advanced past the last row.
    void advance() noexcept;

    // When set to true, new codes may not contain repeating elements.
    void allow_unique_only(bool v) noexcept;

    // Returns a view into the correct code.
    std::span<const int> good_code() const noexcept;

    // Returns true if currently active row represents the last attempt.
    bool last_row() const noexcept;

    // Returns the current State of the Game.
    State state() const noexcept;

    // Resets the game state.
    void reset() noexcept;

    // Resizes the code and resets the Game.
    void resize(std::size_t code_len);

    // Writes the user-provided guess to the currently used row and generates
    // Feedback. Subsequent submission attempt will trigger an assertion error.
    void submit_code(std::span<const int> guess) noexcept;

private:
    static_assert(SCORE_MIN < SCORE_MAX);
    static_assert(Row::CODE_VALUE_NONE < SCORE_MIN);

    // Indicates currently active row.
    std::size_t active_row_num_;

    // Stores the correct code.
    std::vector<int> good_code_;

    // Random number generator.
    utils::Source rand_;

    // Container for Row instances, each representing a single attempt
    // at guessing.
    std::vector<Row> rows_;

    // true allows the generated code to contain unique elements only.
    bool unique_elems_;

    // Returns a reference to the currently active row.
    Row& active_row_mut() noexcept;

    // Generates a new random good_code_.
    void generate_code() noexcept;

    // Debug helper for checking whether rows_[active_row_num_] access
    // is within bounds of rows_.
    [[maybe_unused]] bool within_bounds() const noexcept;
};

} // namespace game
