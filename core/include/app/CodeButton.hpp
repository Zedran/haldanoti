// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <cstddef>

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>

#include "theme/CodeButton.hpp"
#include "ui/Button.hpp"

namespace app {

// A specialized Button that manages a single code element in a row. CodeButton
// allows incrementing and decrementing code value within valid range through
// bound keys and buttons.
class CodeButton final : public ui::Button {
public:
    // Size relative to the height of the CodeButton's container.
    static constexpr sf::Vector2f REL_SIZE{0.5f, 0.5f};

    // Enable the display of text in all instances of CodeButton.
    static void set_show_text(bool show_text) noexcept;

    // Sets the static member styles_.
    static void set_theme(theme::CodeButton theme);

    CodeButton(const sf::Font& font, sf::Vector2f size);

    ~CodeButton();

    // Returns the current value of the stored code element.
    int code_element() const noexcept;

    // Makes CodeButton non-interactive. A wrapper for Button::disable.
    //
    // If retain_active_style is set to true, the style of the CodeButton
    // instance remains set as if it was still active. This is the desired
    // behaviour when user wishes to commit current row - the colors
    // and numbers should still be displayed in such case.
    //
    // If retain_active_style is false, the CodeButton style and text
    // value is set to its "empty" state. This behaviour is desired when
    // the game interface is first initialized and when the game board
    // is reset before beginning of the new game.
    //
    // The retention of active style must never be requested if the value
    // of code_element_ is equal to CODE_VALUE_NONE.
    void disable(bool retain_active_style);

    // Returns true if the code value has been set (is not equal to
    // game::Row::CODE_VALUE_NONE).
    bool is_set() const noexcept;

    // Resets CodeButton instance to its empty state.
    void reset();

    // Sets the specified code value to the CodeButton instance.
    void set_value(int value);

    // Forces CodeButton instance to use its normal style, even when disabled.
    // This cannot be done if code_element_ value is equal to CODE_VALUE_NONE.
    void use_normal_style();

private:
    // Font size relative to the height of CodeButton.
    static constexpr float FONT_REL_SIZE{0.75f};

    // Stores the styles associated with different button states.
    static theme::CodeButton styles_;

    // If true, instances of CodeButton will display text.
    static bool show_text_;

    // Holds current code element value.
    int code_element_;

    // Decreases the code element's value by 1. The value loops around
    // to the maximum once the minimum value is decremented.
    void decrement();

    // Returns the styles_.elements index associated with current code element.
    // It is always equal to code_element_ - 1.
    std::size_t elem_index() const noexcept;

    // Increases the code element's value by 1. The value loops around
    // to the minimum once the maximum value is incremented.
    void increment();

    // Updates CodeButton's text after a new code_element_ value has been set.
    void update_text();
};

} // namespace app
