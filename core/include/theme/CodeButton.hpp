#pragma once

#include <vector>

#include "ui/Button.hpp"

namespace theme {

struct CodeButton {
    // Special style for CodeButtons with unset values.
    ui::Button::Style empty;

    // A vector of styles, one for each unique code value.
    std::vector<ui::Button::Style> elements;
};

} // namespace theme
