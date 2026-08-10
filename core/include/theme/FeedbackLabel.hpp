// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include "ui/Label.hpp"

namespace theme {

struct FeedbackLabel {
    bool show_text;

    ui::Label::Style none;
    ui::Label::Style red;
    ui::Label::Style white;
};

} // namespace theme
