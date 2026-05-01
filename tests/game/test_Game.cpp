#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <array>
#include <span>

#include "game/Feedback.hpp"
#include "game/Game.hpp"
#include "game/State.hpp"

using namespace game;

// Tests whether the Game assumes correct state after construction.
TEST_CASE("Game::Game") {
    constexpr unsigned long SEED = 1;

    const Game g_rand;
    const Game g_seeded{SEED};

    for (const auto& g : {g_rand, g_seeded}) {
        REQUIRE(g.active_row_num() == 0);
        REQUIRE(g.state() == State::Running);

        for (const auto& e : g.good_code()) {
            REQUIRE(e != Row::CODE_VALUE_NONE);
        }
    }
}

// Tests whether submitting code to the Game's Row causes it to assume
// the expected state.
TEST_CASE("Game::submit_code") {
    constexpr unsigned long SEED = 1;

    constexpr std::array<int, Row::ROW_LEN> guess{1, 2, 3, 4};

    Game g{SEED};

    {
        // Making sure that the guess is not the same as the generated code.
        std::span<const int, Row::ROW_LEN> good_code = g.good_code();
        REQUIRE_FALSE(std::equal(good_code.begin(), good_code.end(), guess.begin(), guess.end()));
    }

    g.submit_code(guess);

    // Not advanced, so still 0.
    REQUIRE(g.active_row_num() == 0);
    REQUIRE(g.state() == State::Running);

    // Check whether Row assumed the correct state.
    const Row& r = g.active_row();
    REQUIRE(r.locked());

    std::span<const int, Row::ROW_LEN> code = r.code();
    REQUIRE(std::equal(guess.begin(), guess.end(), code.begin(), code.end()));

    const Feedback fb = r.feedback();
    REQUIRE(fb.red_count == 3);
    REQUIRE(fb.white_count == 0);
}

// Tests State changes during the game.
TEST_CASE("Game::state") {
    constexpr unsigned long SEED = 1;

    // Game running from the moment of construction.
    Game g{SEED};
    REQUIRE(g.state() == State::Running);

    // Game won.
    g.submit_code(g.good_code());
    REQUIRE(g.state() == State::Won);

    // Running again after reset.
    g.reset();
    REQUIRE(g.state() == State::Running);

    constexpr std::array<int, Row::ROW_LEN> guess{1, 2, 3, 4};
    {
        // Making sure that the guess is not the same as the generated code.
        std::span<const int, Row::ROW_LEN> good_code = g.good_code();
        REQUIRE_FALSE(std::equal(good_code.begin(), good_code.end(), guess.begin(), guess.end()));
    }

    // Losing on purpose.
    for (size_t i = 0; i < Game::NUM_ROWS; i++) {
        CAPTURE(i);

        REQUIRE(g.active_row_num() == i);

        g.submit_code(guess);

        if (g.last_row()) {
            REQUIRE(g.state() == State::Lost);
        } else {
            g.advance();
            REQUIRE(g.state() == State::Running);
        }
    }

    // Running again after reset.
    g.reset();
    REQUIRE(g.state() == State::Running);
}
