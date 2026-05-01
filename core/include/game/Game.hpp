#pragma once

#include <array>
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

    // Constructs a new instance of the Game.
    Game();

    // Constructs a new instance of the Game, initializing random number
    // generator with a custom seed.
    explicit Game(const unsigned long seed);

    // Returns a const reference to the currently active row.
    const Row& active_row() const noexcept;

    // Returns the number of currently active row.
    std::size_t active_row_num() const noexcept;

    // Progresses to the next row. Game cannot be advanced past the last row.
    void advance() noexcept;

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
    static_assert(SCORE_MAX - SCORE_MIN + 1 >= Row::ROW_LEN);

    // Indicates currently active row.
    std::size_t active_row_num_;

    // Stores the correct code.
    std::array<int, Row::ROW_LEN> good_code_;

    // Random number generator.
    utils::Source rand_;

    // Container for Row instances, each representing a single attempt
    // at guessing.
    std::array<Row, NUM_ROWS> rows_;

    // Returns a reference to the currently active row.
    Row& active_row_mut() noexcept;

    // Generates a new random good_code_.
    void generate_code() noexcept;

    // Debug helper for checking whether rows_[active_row_num_] access
    // is within bounds of rows_.
    [[maybe_unused]] bool within_bounds() const noexcept;
};

} // namespace game
