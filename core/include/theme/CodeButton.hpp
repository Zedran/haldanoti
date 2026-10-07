// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <vector>

#include <nlohmann/json.hpp>

#include "ui/Button.hpp"
#include "utils/json.hpp" // IWYU pragma: keep

namespace theme {

// Style used by CodeButton class instances.
struct CodeButton {
    // Special style for CodeButtons with unset values.
    ui::Button::Style empty;

    // A vector of styles, one for each unique code value.
    std::vector<ui::Button::Style> elements;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    CodeButton,
    empty,
    elements
);

} // namespace theme
