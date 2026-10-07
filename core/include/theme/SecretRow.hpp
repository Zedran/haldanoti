// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <nlohmann/json.hpp>

#include "ui/Box.hpp"
#include "ui/Label.hpp"
#include "utils/json.hpp" // IWYU pragma: keep

namespace theme {

// Style of the SecretRow class.
struct SecretRow {
    // Outer box.
    ui::Box::Style box;

    // Box with code buttons.
    ui::Box::Style code_box;

    // Info label: no hint.
    ui::Label::Style info_running;

    // Info label: hint displayed.
    ui::Label::Style info_running_hint;

    // Info label: lost.
    ui::Label::Style info_lost;

    // Info label: won.
    ui::Label::Style info_won;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    SecretRow,
    box,
    code_box,
    info_running,
    info_running_hint,
    info_lost,
    info_won
);

} // namespace theme
