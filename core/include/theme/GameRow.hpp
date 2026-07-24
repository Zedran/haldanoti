// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include "theme/CodeButton.hpp"
#include "theme/FeedbackLabel.hpp"
#include "theme/RowBoxStyle.hpp"
#include "ui/Button.hpp"

namespace theme {

struct GameRow {
    // Outer box.
    RowBoxStyle box;

    // Box with code buttons.
    RowBoxStyle code_box;

    // Box holding feedback labels.
    RowBoxStyle fb_box;

    // Box containing the ok button or row number.
    RowBoxStyle ok_box;

    // Passed to CodeButton to set its styles_ static member.
    const CodeButton* code_button;

    // Passed to FeedbackLabel to set its theme-related static members.
    FeedbackLabel fb_label;

    // Style for the ok button.
    ui::Button::Style ok_button;
};

} // namespace theme
