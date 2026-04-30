#pragma once

#include <array>
#include <cstddef>
#include <span>

#include "game/Feedback.hpp"

namespace game {

// Row represents a single attempt at guessing the code.
class Row {
public:
    // If set as value for code element, it indicates that no meaningful value
    // was set.
    static constexpr int CODE_VALUE_NONE = 0;

    // The number of elements in the code.
    static constexpr std::size_t ROW_LEN = 4;

    // Constructs a new Row.
    Row() noexcept;

    // Returns the view into the current code held by the Row.
    std::span<const int, ROW_LEN> code() const noexcept;

    // Writes the user's guess to the user_code_ field and generates Feedback
    // against good_code. Row becomes locked after calling commit. Subsequent
    // call to commit will trigger an assertion error.
    void commit(std::span<const int, ROW_LEN> good_code, std::span<const int, ROW_LEN> guess) noexcept;

    // Returns the Feedback for the Row.
    Feedback feedback() const noexcept;

    // Returns true if the Row has been locked.
    bool locked() const noexcept;

    // Resets the Row instance to the default state.
    void reset() noexcept;

private:
    // Code written to the Row.
    std::array<int, ROW_LEN> code_;

    // Feedback for the Row.
    Feedback feedback_;

    // Row becomes locked after the call to the commit member function.
    bool locked_;
};

} // namespace game
