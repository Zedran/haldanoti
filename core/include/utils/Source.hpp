#pragma once

#include <random>

namespace utils {

// Random number generator.
class Source {
    std::uniform_int_distribution<int> dist_;
    std::default_random_engine         re_;

public:
    // Creates a new Source, seeding it from random_device.
    Source(const int low, const int high);

    // Creates a new Source, seeding it from the specified seed value.
    Source(const int low, const int high, const unsigned long seed);

    // Generates a new random number.
    int get();
};

} // namespace utils
