// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <algorithm>
#include <cassert>

#include "game/Row.hpp"
#include "game/helpers.hpp"

namespace game {

Row::Row(std::size_t len) : code_(len, CODE_VALUE_NONE), feedback_{}, locked_{} {}

Row::~Row() = default;

std::span<const int> Row::code() const noexcept {
    return code_;
}

void Row::commit(std::span<const int> good_code, std::span<const int> guess) noexcept {
    assert(!locked_);

    assert(guess.size() == code_.size());
    std::copy(guess.begin(), guess.end(), code_.begin());

    feedback_ = internal::compare_codes(good_code, guess);
    locked_   = true;
}

Feedback Row::feedback() const noexcept {
    return feedback_;
}

bool Row::locked() const noexcept {
    return locked_;
}

void Row::reset() noexcept {
    std::fill(code_.begin(), code_.end(), CODE_VALUE_NONE);
    feedback_ = Feedback{};
    locked_   = false;
}

std::size_t Row::size() const noexcept {
    return code_.size();
}

} // namespace game
