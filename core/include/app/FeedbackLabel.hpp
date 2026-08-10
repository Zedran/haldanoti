// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <mutex>

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>

#include "lang/FeedbackLabel.hpp"
#include "theme/FeedbackLabel.hpp"
#include "ui/Label.hpp"

namespace app {

// A specialized Label that stores a single feedback element for the code
// submitted in its row.
//
// FeedbackLabel instances are not tied to any particular code elements. Their
// controller assigns them feedback values from left to right. Red pins
// are assigned first, white pins follow. If there are less feedback values
// than available pins, the remaining pins are left empty.
class FeedbackLabel final : public ui::Label {
public:
    // Represents different states that FeedbackLabel can assume.
    enum class Pin {
        // No pin set. The default state of unused row. In committed rows,
        // it indicates that a code element is neither of correct value (color)
        // nor in the correct place.
        None,

        // Red pin set. Indicates that a code element has correct value (color)
        // and is in the correct place.
        Red,

        // White pin set. Indicates that a code element has correct value
        // (color), but is in an incorrect place.
        White
    };

    // Size relative to the height of the FeedbackLabel's container.
    static constexpr sf::Vector2f REL_SIZE{0.25f, 0.25f};

    // Sets the static member lang_. This operation is only done once.
    static void set_lang(lang::FeedbackLabel lang);

    // Sets the static member styles_. This operation is only done once.
    static void set_theme(theme::FeedbackLabel theme);

    FeedbackLabel(const sf::Font& font, sf::Vector2f size);

    ~FeedbackLabel();

    // Returns currently set Pin value.
    Pin get_pin() const noexcept;

    // Resets FeedbackLabel instance to its empty state.
    void reset();

    // Assigns a new Pin value to FeedbackLabel instance.
    void set_pin(Pin pin);

private:
    // Font size relative to the height of FeedbackLabel.
    static constexpr float FONT_REL_SIZE{0.75f};

    // Contains text value set to the FeedbackLabel, depending on its state
    // and styles_.show_text.
    static lang::FeedbackLabel lang_;

    // Stores the styles associated with different Pin values.
    static theme::FeedbackLabel styles_;

    // This once_flag is used by the static set_lang member function.
    static std::once_flag lang_set_;

    // This once_flag is used by the static set_theme member function.
    static std::once_flag styles_set_;

    // Holds current Pin assigned to the FeedbackLabel instance.
    Pin pin_;

    // Updates FeedbackLabel's text after a new style has been set.
    void update_text();
};

} // namespace app
