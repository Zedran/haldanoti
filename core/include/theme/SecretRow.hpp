// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include "ui/Box.hpp"
#include "ui/Label.hpp"

namespace theme {

struct SecretRow {
    // Outer box.
    ui::Box::Style box;

    // Box with code buttons.
    ui::Box::Style code_box;

    // Info label: no message.
    ui::Label::Style info_running;

    // Info label: lost.
    ui::Label::Style info_lost;

    // Info label: won.
    ui::Label::Style info_won;
};

} // namespace theme
