// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <utility>

namespace utils {

template <class F>
class DeferredAction {
public:
    explicit DeferredAction(F func) noexcept : func_{std::move(func)} {}

    ~DeferredAction() {
        func_();
    };

private:
    F func_;
};

template <class F>
[[nodiscard]] auto defer(F&& func) noexcept {
    return DeferredAction{std::move(func)};
}

} // namespace utils
