// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <nlohmann/json.hpp>

#include "theme/CodeButton.hpp"
#include "theme/FeedbackLabel.hpp"
#include "theme/GameRowBase.hpp"

namespace theme {

// Style used by all instances of the GameRow class.
struct GameRow {
    // A part of the GameRow's style used exclusively by GameRow.
    GameRowBase base;

    // Passed to CodeButton to set its theme-related static members.
    CodeButton code_button;

    // Passed to FeedbackLabel to set its theme-related static members.
    FeedbackLabel fb_label;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    GameRow,
    base,
    code_button,
    fb_label
);

} // namespace theme
