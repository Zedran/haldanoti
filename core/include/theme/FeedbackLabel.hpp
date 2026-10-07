// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <nlohmann/json.hpp>

#include "ui/Label.hpp"
#include "utils/json.hpp" // IWYU pragma: keep

namespace theme {

// Style of the FeedbackLabel class.
struct FeedbackLabel {
    ui::Label::Style none;
    ui::Label::Style red;
    ui::Label::Style white;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    FeedbackLabel,
    none,
    red,
    white
);

} // namespace theme
