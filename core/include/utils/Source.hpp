#pragma once

#include <random>
#include <span>

namespace utils {

// Random number generator.
class Source {
public:
    // Creates a new Source, seeding it from random_device.
    Source(const int low, const int high);

    // Creates a new Source, seeding it from the specified seed value.
    Source(const int low, const int high, const unsigned long seed);

    ~Source();

    // Generates a new random number.
    int get();

    // Fills the specified container with unique random numbers.
    void read(std::span<int> out);

private:
    std::uniform_int_distribution<int> dist_;
    std::default_random_engine         re_;
};

} // namespace utils
