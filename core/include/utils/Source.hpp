// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <optional>
#include <random>
#include <span>

namespace utils {

// Random number generator.
class Source {
public:
    // Constructs a new Source, seeding the generator with pseudorandom number
    // or a custom seed value.
    Source(const int low, const int high, std::optional<unsigned long> seed = std::nullopt);

    ~Source();

    // Generates a new random number.
    int get();

    // Fills the specified container with random numbers.
    void read(std::span<int> out);

    // Fills the specified container with unique random numbers.
    void read_unique(std::span<int> out);

private:
    std::uniform_int_distribution<int> dist_;
    std::default_random_engine         re_;
};

} // namespace utils
