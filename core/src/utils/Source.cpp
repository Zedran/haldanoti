// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

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

Source::~Source() = default;

int Source::get() {
    return dist_(re_);
}

void Source::read_unique(std::span<int> out) {
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

} // namespace utils
