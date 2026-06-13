#include <cassert>
#include <mutex>
#include <stdexcept>
#include <string>

#include "app/CodeButton.hpp"
#include "game/Game.hpp"
#include "game/Row.hpp"
#include "ui/Button.hpp"
#include "utils/debug.hpp"

namespace app {

std::once_flag CodeButton::styles_set_{};

theme::CodeButton CodeButton::styles_{};

CodeButton::CodeButton(const sf::Font& font, sf::Vector2f size)
    : ui::Button{font, size, styles_.empty, std::to_string(game::Row::CODE_VALUE_NONE), FONT_REL_SIZE * size.y},
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
        Label::set_style(styles_.elements[elem_index()].active);
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
    set_text(std::to_string(code_element_));
    set_style(styles_.empty);
}

void CodeButton::set_theme(theme::CodeButton theme) {
    std::call_once(styles_set_, [theme] {
        CodeButton::styles_ = theme;

        if (CodeButton::styles_.elements.size() != game::Game::NUM_UNIQUE_ELEMS) {
            throw std::logic_error{
                "incorrect number of CodeButton styles (" +
                std::to_string(styles_.elements.size()) +
                ')'
            };
        }
    });
}

void CodeButton::set_value(int value) {
    assert(value >= game::Game::SCORE_MIN);
    assert(value <= game::Game::SCORE_MAX);

    code_element_ = value;
    set_text(std::to_string(code_element_));
    set_style(styles_.elements[elem_index()]);
}

} // namespace app
