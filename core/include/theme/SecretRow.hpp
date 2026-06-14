#pragma once

#include "theme/CodeButton.hpp"
#include "ui/Box.hpp"
#include "ui/Label.hpp"

namespace theme {

struct SecretRow {
    // Outer box.
    ui::Box::Style box;

    // Box with code buttons.
    ui::Box::Style code_box;

    // Passed to CodeButton to set its styles_ static member.
    const CodeButton* code_button;

    // Info label: no message.
    ui::Label::Style info_none;

    // Info label: lost.
    ui::Label::Style info_lost;

    // Info label: won.
    ui::Label::Style info_won;
};

} // namespace theme
