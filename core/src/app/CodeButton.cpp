// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <cassert>
#include <stdexcept>
#include <string>
#include <utility>

#include "app/CodeButton.hpp"
#include "game/Game.hpp"
#include "game/Row.hpp"
#include "ui/Button.hpp"
#include "utils/debug.hpp"

namespace app {

theme::CodeButton CodeButton::styles_{};

bool CodeButton::show_text_{};

CodeButton::CodeButton(const sf::Font& font, sf::Vector2f size)
    : ui::Button{
          font,
          size,
          styles_.empty,
          CodeButton::show_text_ ? std::to_string(game::Row::CODE_VALUE_NONE) : "",
          static_cast<unsigned int>(FONT_REL_SIZE * size.y),
      },
      code_element_{game::Row::CODE_VALUE_NONE} {
    bind(sf::Mouse::Button::Left, [this] { this->increment(); });
    bind(sf::Mouse::Button::Right, [this] { this->decrement(); });
    disable(false);
}

CodeButton::~CodeButton() = default;

int CodeButton::code_element() const noexcept {
    return code_element_;
}

void CodeButton::decrement() {
    switch (code_element_) {
    case game::Row::CODE_VALUE_NONE:
    case game::Game::SCORE_MIN:      set_value(game::Game::SCORE_MAX); break;
    default:                         set_value(code_element_ - 1);
    }
}

void CodeButton::disable(bool retain_active_style) {
    Button::disable();
    if (retain_active_style) {
        use_normal_style();
    }
}

std::size_t CodeButton::elem_index() const noexcept {
    std::size_t i = static_cast<std::size_t>(code_element_) - game::Game::SCORE_MIN;
    dbg("code_element = {}, elem_index() -> {}", code_element_, i);
    return i;
}

void CodeButton::increment() {
    switch (code_element_) {
    case game::Row::CODE_VALUE_NONE:
    case game::Game::SCORE_MAX:      set_value(game::Game::SCORE_MIN); break;
    default:                         set_value(code_element_ + 1);
    }
}

bool CodeButton::is_set() const noexcept {
    return code_element_ != game::Row::CODE_VALUE_NONE;
}

void CodeButton::reset() {
    code_element_ = game::Row::CODE_VALUE_NONE;
    update_text();
    set_style(styles_.empty);
}

void CodeButton::set_show_text(bool show_text) noexcept {
    show_text_ = show_text;
}

void CodeButton::set_theme(theme::CodeButton theme) {
    CodeButton::styles_ = std::move(theme);

    if (CodeButton::styles_.elements.size() != game::Game::NUM_UNIQUE_ELEMS) {
        throw std::logic_error{
            "incorrect number of CodeButton styles (" +
            std::to_string(styles_.elements.size()) +
            ')'
        };
    }
}

void CodeButton::set_value(int value) {
    assert(value >= game::Game::SCORE_MIN);
    assert(value <= game::Game::SCORE_MAX);

    code_element_ = value;
    update_text();
    set_style(styles_.elements[elem_index()]);
}

void CodeButton::update_text() {
    if (CodeButton::show_text_) {
        set_text(std::to_string(code_element_));
    }
}

void CodeButton::use_normal_style() {
    assert(code_element_ != game::Row::CODE_VALUE_NONE);
    Label::set_style(styles_.elements[elem_index()].normal);
}

} // namespace app
