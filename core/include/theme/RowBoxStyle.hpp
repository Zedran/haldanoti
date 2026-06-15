#pragma once

#include "ui/Box.hpp"

namespace theme {

// Boxes that constitute GameRow require different appearance depending
// on whether their row is currently locked.
struct RowBoxStyle {
    ui::Box::Style active;
    ui::Box::Style inactive;
};

} // namespace theme
