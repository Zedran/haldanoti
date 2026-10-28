// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <cstddef>
#include <vector>

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

#include "app/CodeButton.hpp"
#include "app/FeedbackLabel.hpp"
#include "game/Feedback.hpp"
#include "lang/GameRow.hpp"
#include "theme/GameRow.hpp"
#include "theme/GameRowBase.hpp"
#include "ui/Box.hpp"
#include "ui/Button.hpp"

namespace app {

// GameRow handles player interaction during a single code-guessing attempt.
class GameRow final : public ui::Box {
public:
    // Size relative to outer container.
    static constexpr sf::Vector2f REL_SIZE{1.0f, 0.077f};

    // Determines the behavior of the all_set member function. This setting
    // must be coherent with the game's unique_only setting.
    static void allow_unique_only(bool v) noexcept;

    // Sets the value of the static member lang_.
    static void set_lang(lang::GameRow lang) noexcept;

    // Sets the static member styles_. force_fb_chars is relayed down to
    // FeedbackLabel::set_theme.
    static void set_theme(theme::GameRow theme) noexcept;

    GameRow(const sf::Font& font, sf::Vector2f size, std::size_t code_len, int row_number);

    ~GameRow();

    // Returns true if every CodeButton within the row has a code value
    // assigned.
    //
    // The algorithm used to determine a successfull assignment of every code
    // value varies, depending on whether all characters in the secret code are
    // required to be unique or not.
    //
    // With duplicates allowed in the secret code, all_set returns true if
    // every code value is not equal to game::Row::CODE_VALUE_NONE.
    //
    // If the unique requirement is in force, all_set returns true if every
    // code value is unique and is not equal to game::Row::CODE_VALUE_NONE.
    bool all_set() const noexcept;

    // Returns a vector of code values retrieved from CodeButtons within
    // the row.
    [[nodiscard]] std::vector<int> get_code() const noexcept;

    // Returns true if the GameRow instance is locked.
    bool is_locked() const noexcept;

    // Locks the GameRow instance, making its elements non-interactive.
    // If commit is true, the GameRow will only be locked if every
    // CodeButton within it has a value assigned.
    void lock(bool commit);

    // Resets the GameRow instance to its initial state.
    void reset();

    // Resizes the GameRow to the specified code length.
    void resize(std::size_t code_len);

    // Sets the pins in FeedbackLabels according to the provided argument.
    void set_feedback(game::Feedback fb);

    // Unlocks the GameRow instance, making its elements interactive.
    void unlock();

private:
    // Size of the code box relative to the dimensions of the outer container.
    static constexpr sf::Vector2f CODE_BOX_REL_SIZE{0.46f, 1.0f};

    // Size of the feedback box relative to the dimensions of the outer
    // container.
    static constexpr sf::Vector2f FB_BOX_REL_SIZE{0.33f, 1.0f};

    // Size of the ok box relative to the dimensions of the outer container.
    static constexpr sf::Vector2f OK_BOX_REL_SIZE{0.21f, 1.0f};

    // Font size for ok button, relative to the height of the outer container.
    static constexpr float OK_BUTTON_FONT_REL_SIZE{0.3f};

    // Size of the ok box relative to the dimensions of the outer container.
    static constexpr sf::Vector2f OK_BUTTON_REL_SIZE{0.75f, 0.5f};

    // Determines which row evaluation strategy should be used by all_set.
    static bool allow_unique_only_;

    // Contains text value set to the ok Button when the GameRow is active.
    static sf::String ok_button_text_;

    // Stores the styles associated with different box states.
    static theme::GameRowBase styles_;

    // Non-owning pointer required for modifying styles of to the code box.
    ui::Box* code_box_;

    // Non-owning pointer required for modifying styles of the feedback box.
    ui::Box* fb_box_;

    // Non-owning pointer required for modifying styles of the ok box.
    ui::Box* ok_box_;

    // Holds non-owning pointers to CodeButton instances. Used to manipulate
    // CodeButtons owned by the GameRow instance.
    std::vector<CodeButton*> code_buttons_;

    // Holds non-owning pointers to FeedbackLabel instances. Used to manipulate
    // FeedbackLabels within the GameRow instance.
    std::vector<FeedbackLabel*> fb_labels_;

    // Non-owning pointer required for modifying styles of the ok button.
    // When the GameRow is locked, this button serves as a row number
    // indicator. For unlocked rows, it becomes a button that commits
    // the user's guess.
    ui::Button* ok_button_;

    // When the GameRow instance is locked, no input via bindings is accepted.
    bool locked_;

    // Row number in string form, stored for the ok button.
    sf::String row_num_;

    // Called by all_set if allow_unique_only_ is false.
    bool all_set_any_kind() const noexcept;

    // Called by all_set if allow_unique_only_ is true.
    bool all_set_if_unique() const noexcept;

    // Sets the correct box styles following locking and unlocking
    // of the GameRow instance.
    void update_box_styles();
};

} // namespace app
