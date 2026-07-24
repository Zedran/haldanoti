// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

namespace game {

// Feedback the player receives after submitting their guess.
struct Feedback {
    // Number of elements that have correct value and placement.
    int red_count;

    // Number of elements that have correct value, but not placement.
    int white_count;
};

} // namespace game
