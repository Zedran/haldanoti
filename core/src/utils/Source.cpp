#include <algorithm>
#include <cassert>
#include <unordered_set>

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

void Source::fill(std::span<int> out) {
    // Since out is filled with unique values, ensure that its length does not
    // exceed the number of distinct values that Source can provide.
    assert(dist_.max() - dist_.min() + 1 >= static_cast<int>(out.size()));

    std::unordered_set<int> used;

    std::for_each(out.begin(), out.end(), [&](auto& e) {
        while (true) {
            const int n = get();

            if (used.insert(n).second) {
                e = n;
                break;
            }
        }
    });
}

int Source::get() {
    return dist_(re_);
}

} // namespace utils
