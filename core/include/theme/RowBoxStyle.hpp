// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <nlohmann/json.hpp>

#include "ui/Box.hpp"
#include "utils/json.hpp" // IWYU pragma: keep

namespace theme {

// Boxes that constitute GameRow require different appearance depending
// on whether their row is currently locked.
struct RowBoxStyle {
    ui::Box::Style active;
    ui::Box::Style inactive;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    RowBoxStyle,
    active,
    inactive
);

} // namespace theme
