// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <algorithm>
#include <cassert>

#include "game/Row.hpp"
#include "game/helpers.hpp"

namespace game {

Row::Row() noexcept : code_{}, feedback_{}, locked_{} {
    code_.fill(CODE_VALUE_NONE);
}

Row::~Row() = default;

std::span<const int, Row::ROW_LEN> Row::code() const noexcept {
    return code_;
}

void Row::commit(std::span<const int, ROW_LEN> good_code, std::span<const int, ROW_LEN> guess) noexcept {
    assert(!locked_);

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
    code_.fill(CODE_VALUE_NONE);
    feedback_ = Feedback{};
    locked_   = false;
}

} // namespace game
