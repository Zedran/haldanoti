#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <array>
#include <span>

#include "game/Feedback.hpp"
#include "game/Row.hpp"

using namespace game;

// Tests whether Row assumes the correct state after construction.
TEST_CASE("Row::Row") {
    std::array<int, Row::ROW_LEN> empty{};
    empty.fill(Row::CODE_VALUE_NONE);

    const Row r;

    // Empty, ready for writing.
    REQUIRE_FALSE(r.locked());

    // No pins in Feedback.
    Feedback fb = r.feedback();
    REQUIRE(fb.red_count == 0);
    REQUIRE(fb.white_count == 0);

    // All code elements should be set to CODE_VALUE_NONE.
    std::span<const int, Row::ROW_LEN> code = r.code();
    CAPTURE(empty);
    CAPTURE(code);
    REQUIRE(std::equal(empty.begin(), empty.end(), code.begin(), code.end()));
}

// Tests the correctness of the Row::commit function.
TEST_CASE("Row::commit") {
    constexpr std::array<int, Row::ROW_LEN> good_code{1, 2, 3, 4};
    constexpr std::array<int, Row::ROW_LEN> guess{1, 2, 3, 4};

    Row r;

    // Committing locks the Row.
    r.commit(good_code, guess);
    REQUIRE(r.locked());

    // Values in guess should be written to Row::code_.
    std::span<const int, Row::ROW_LEN> code = r.code();
    CAPTURE(guess);
    CAPTURE(code);
    REQUIRE(std::equal(guess.begin(), guess.end(), code.begin(), code.end()));

    // Valid values in Feedback.
    const Feedback fb = r.feedback();
    REQUIRE(fb.red_count == 4);
    REQUIRE(fb.white_count == 0);
}

// Tests whether the Row assumes the correct state after reset.
TEST_CASE("Row::reset") {
    std::array<int, Row::ROW_LEN> empty{};
    empty.fill(Row::CODE_VALUE_NONE);

    constexpr std::array<int, Row::ROW_LEN> good_code{1, 2, 3, 4};
    constexpr std::array<int, Row::ROW_LEN> guess{1, 2, 3, 4};

    Row r;

    r.commit(good_code, guess);

    // Resetting the Row unlocks it.
    r.reset();
    REQUIRE_FALSE(r.locked());

    // The code is empty again.
    std::span<const int, Row::ROW_LEN> code = r.code();
    CAPTURE(empty);
    CAPTURE(code);
    REQUIRE(std::equal(empty.begin(), empty.end(), code.begin(), code.end()));

    // No pins in Feedback after reset.
    const Feedback fb = r.feedback();
    REQUIRE(fb.red_count == 0);
    REQUIRE(fb.white_count == 0);
}
