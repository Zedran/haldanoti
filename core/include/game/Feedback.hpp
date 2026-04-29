#pragma once

namespace game::internal {

// Feedback the player receives after submitting their guess.
struct Feedback {
    // Number of elements that have correct value and placement.
    int red_count;

    // Number of elements that have correct value, but not placement.
    int white_count;
};

} // namespace game::internal
