// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <catch2/catch_test_macros.hpp>

#include <array>

#include "utils/Source.hpp"

TEST_CASE("Source::read") {
    constexpr std::size_t T = 8;

    constexpr int MIN = 1;
    constexpr int MAX = 8;

    constexpr unsigned long SEED = 1;

    utils::Source rand{MIN, MAX, SEED};

    std::array<int, T> arr;
    rand.read(arr);

    bool has_min{}, has_max{};

    for (const auto& e : arr) {
        REQUIRE(e >= MIN);
        REQUIRE(e <= MAX);

        if (e == MIN) {
            has_min = true;
        } else if (e == MAX) {
            has_max = true;
        }
    }

    REQUIRE(has_min);
    REQUIRE(has_max);
}
