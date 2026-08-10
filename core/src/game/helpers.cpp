// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

#include "game/Row.hpp"
#include "game/helpers.hpp"

namespace game::internal {

Feedback compare_codes(std::span<const int> good_code, std::span<const int> user_code) noexcept {
    assert(user_code.size() == good_code.size());

    std::vector<int> gc(good_code.begin(), good_code.end());
    std::vector<int> uc(user_code.begin(), user_code.end());

    Feedback fb{};

    for (std::size_t i = 0; i < uc.size(); i++) {
        if (uc[i] == gc[i]) {
            fb.red_count++;
            gc[i] = game::Row::CODE_VALUE_NONE;
        }
    }

    for (std::size_t i = 0; i < gc.size(); i++) {
        if (gc[i] == game::Row::CODE_VALUE_NONE) {
            continue;
        }

        const auto it = std::find(uc.begin(), uc.end(), gc[i]);

        if (it != uc.end()) {
            fb.white_count++;
            uc[static_cast<std::size_t>(std::distance(uc.begin(), it))] = game::Row::CODE_VALUE_NONE;
        }
    }

    return fb;
}

} // namespace game::internal
