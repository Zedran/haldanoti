#include "utils/Source.hpp"

namespace utils {

Source::Source(const int low, const int high) : dist_{low, high} {
    std::random_device                           rd;
    std::uniform_int_distribution<unsigned long> rdist;
    re_.seed(rdist(rd));
}

Source::Source(const int low, const int high, const unsigned long seed) : dist_{low, high} {
    re_.seed(seed);
}

int Source::get() {
    return dist_(re_);
}

} // namespace utils
