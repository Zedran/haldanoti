#pragma once

#include <span>

#include "game/Feedback.hpp"

namespace game::internal {

Feedback compare_codes(std::span<const int> good_code, std::span<const int> user_code) noexcept;

} // namespace game::internal
