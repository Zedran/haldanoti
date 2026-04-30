#include <catch2/catch_test_macros.hpp>

#include <array>
#include <cstddef>

#include "game/Feedback.hpp"
#include "game/helpers.hpp"

TEST_CASE("compare_codes") {
    using namespace game;
    using namespace game::internal;

    constexpr std::size_t ARR_LEN = 4;

    struct test_data {
        std::array<int, ARR_LEN> good_code_;
        std::array<int, ARR_LEN> user_code_;

        Feedback expected;
    };

    constexpr test_data cases[]{
        {{1, 2, 3, 4}, {1, 2, 3, 4}, {4, 0}},
        {{1, 2, 3, 4}, {1, 1, 1, 1}, {1, 0}},
        {{1, 2, 3, 4}, {4, 3, 2, 1}, {0, 4}},
        {{1, 2, 3, 4}, {1, 5, 4, 6}, {1, 1}},
        {{1, 2, 3, 4}, {5, 6, 7, 8}, {0, 0}},
    };

    for (const auto& c : cases) {
        CAPTURE(c.good_code_, c.user_code_);

        const Feedback out = compare_codes(c.good_code_, c.user_code_);

        REQUIRE(out.red_count == c.expected.red_count);
        REQUIRE(out.white_count == c.expected.white_count);
    }
}
