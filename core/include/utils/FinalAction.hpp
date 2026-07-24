// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

namespace utils {

template <class F>
struct FinalAction {
    F act;

    explicit FinalAction(F f) : act(f) {}
    ~FinalAction() { act(); };
};

template <class F>
[[nodiscard]] auto finally(F f) {
    return FinalAction{f};
}

} // namespace utils
