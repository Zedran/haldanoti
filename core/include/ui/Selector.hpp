// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <cstddef>
#include <vector>

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

#include "ui/Box.hpp"
#include "ui/Button.hpp"
#include "ui/Label.hpp"

namespace ui {

// Selector allows users to select their preference from a set of options.
// It does not own or handle the original data - a vector of string
// representation of the available options is required to operate the Selector.
class Selector : public ui::Box {
public:
    struct Style {
        Box::Style    box;
        Label::Style  label;
        Button::Style button;
    };

    // Constructs a new selector. The entries vector is used to display
    // the available options. It is copied into the class.
    Selector(
        const sf::Font&         font,
        sf::Vector2f            size,
        Style                   style,
        sf::String              label_text,
        std::vector<sf::String> entries
    );

    virtual ~Selector();

    // Returns an index of the currently displayed value in the underlying
    // entries vector.
    std::size_t get_index() const noexcept;

    // Get string value that is currently set in the Selector.
    sf::String get_value() const;

    // Set the chosen value indicated to by index. Throws if index value is out
    // ouf bounds of the underlying entries vector.
    void set_value(std::size_t index);

    // Sets v as current value of the Selector. If none of the Selector's
    // entries matches v, throws logic_error.
    void set_value(const sf::String& v);

private:
    // Size of the description Label relative to the outer Box.
    static constexpr sf::Vector2f LABEL_REL_SIZE{0.6f, 0.75f};

    // Size of the Selector's Label relative to the right Box.
    static constexpr sf::Vector2f LABEL_TO_RBOX_REL_SIZE{0.3f, 1.0f};

    // Entries to display in the Selector's Label.
    std::vector<sf::String> entries_;

    // Index of the currently displayed entry.
    std::size_t index_;

    // Non-owning pointer required for accessing the Selector's Label.
    Label* sel_label_;

    void decrement();

    void increment();
};

} // namespace ui
