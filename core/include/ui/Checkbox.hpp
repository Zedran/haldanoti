// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

#include "ui/Box.hpp"
#include "ui/Button.hpp"
#include "ui/Label.hpp"

namespace ui {

class Checkbox : public Box {
public:
    struct Style {
        ui::Box::Style    box;
        ui::Button::Style button_off;
        ui::Button::Style button_on;
        ui::Label::Style  label;
    };

    Checkbox(
        const sf::Font& font,
        sf::Vector2f    size,
        Checkbox::Style style,
        sf::String      label_text,
        sf::String      check_mark
    );

    virtual ~Checkbox();

    bool get_state() const noexcept;

    void set_state(bool s);

private:
    // Size of the label relative to the outer Box.
    static constexpr sf::Vector2f LABEL_REL_SIZE{0.6f, 0.75f};

    // Size of the label relative to the size.y of the outer Box.
    static constexpr sf::Vector2f CHECKBOX_REL_SIZE{0.6f, 0.6f};

    // None-owning pointer to the Button, required to manipulate its style.
    ui::Button* cb_;

    // Text displayed inside the Button when the box is "checked".
    sf::String check_mark_;

    bool state_;

    Style style_;

    void enable();

    void disable();

    void flip_state();
};

} // namespace ui
