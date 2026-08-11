// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <span>

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

    // Constructs a new instance of the Game.
    explicit Game(bool repetitions);

    // Constructs a new instance of the Game, initializing random number
    // generator with a custom seed.
    Game(bool unique_elems, const unsigned long seed);

    // Prevents Game(bool) from interpreting unsigned int as bool when calling
    // Game{seed} by mistake.
    template <std::integral T>
    Game(T) = delete;

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
    std::span<const int, Row::ROW_LEN> good_code() const noexcept;

    // Returns true if currently active row represents the last attempt.
    bool last_row() const noexcept;

    // Returns the current State of the Game.
    State state() const noexcept;

    // Resets the game state.
    void reset() noexcept;

    // Writes the user-provided guess to the currently used row and generates
    // Feedback. Subsequent submission attempt will trigger an assertion error.
    void submit_code(std::span<const int, Row::ROW_LEN> guess) noexcept;

private:
    static_assert(SCORE_MIN < SCORE_MAX);
    static_assert(Row::CODE_VALUE_NONE < SCORE_MIN);
    static_assert(NUM_UNIQUE_ELEMS >= Row::ROW_LEN);

    // Indicates currently active row.
    std::size_t active_row_num_;

    // Stores the correct code.
    std::array<int, Row::ROW_LEN> good_code_;

    // Random number generator.
    utils::Source rand_;

    // Container for Row instances, each representing a single attempt
    // at guessing.
    std::array<Row, NUM_ROWS> rows_;

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
