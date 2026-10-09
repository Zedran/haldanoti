// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <nlohmann/json.hpp>

#include "theme/RowBoxStyle.hpp"
#include "ui/Button.hpp"
#include "utils/json.hpp" // IWYU pragma: keep

namespace theme {

// Style elements used exclusively by app::GameRow. They are separated into
// this struct to decouple them from the styles of CodeButton and FeedbackLabel
// classes. The separation allows app::GameRow to let go of the style elements
// it does not use. Without it, theme::CodeButton would needlessly hold heap
// memory, being stored both in app::GameRow and in app::CodeButton. Moving
// theme::CodeButton would free the heap, but would also introduce the risk
// of using the moved-from (and still useless) style in the GameRow's logic.
struct GameRowBase {
    // Outer box.
    RowBoxStyle box;

    // Box with code buttons.
    RowBoxStyle code_box;

    // Box holding feedback labels.
    RowBoxStyle fb_box;

    // Box containing the ok button or row number.
    RowBoxStyle ok_box;

    // Style for the ok button.
    ui::Button::Style ok_button;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    GameRowBase,
    box,
    code_box,
    fb_box,
    ok_box,
    ok_button
);

} // namespace theme
