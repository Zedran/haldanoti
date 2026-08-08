// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include "ui/Button.hpp"
#include "ui/Binding.hpp"
#include "utils/FinalAction.hpp"
#include "utils/utils.hpp"

namespace ui {

Button::Button(
    const sf::Font&             font,
    sf::Vector2f                size,
    Style                       style,
    sf::String                  text,
    std::optional<unsigned int> font_size
) : Label{font, size, style.normal, std::move(text), font_size},
    pressed_by_{},
    state_{State::Normal},
    style_{style} {}

Button::~Button() = default;

bool Button::check_collision(sf::Vector2i pos) {
    return utils::detect_collision(get_bounds(), pos);
}

void Button::disable() noexcept {
    pressed_by_ = nullptr;
    state_      = State::Disabled;
    update();
}

void Button::enable() noexcept {
    state_ = State::Normal;
    update();
}

void Button::handle_event(const sf::Event& event) {
    if (state_ == State::Disabled) {
        return;
    }

    const auto update = utils::finally([this] { this->update(); });

    if (const auto* e = event.getIf<sf::Event::MouseMoved>()) {
        handle_mouse_move(*e);
        return;
    }

    if (pressed_by_) {
        if (const auto* e = event.getIf<sf::Event::MouseButtonReleased>()) {
            if (handle_release(*e, *pressed_by_)) {
                return;
            }
        }

        if (const auto* e = event.getIf<sf::Event::KeyReleased>()) {
            handle_release(*e, *pressed_by_);
        }
        return;
    }

    for (auto& b : bindings_) {
        if (const auto* e = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (handle_press(*e, b)) {
                return;
            }
        }

        if (const auto* e = event.getIf<sf::Event::MouseButtonReleased>()) {
            if (handle_release(*e, b)) {
                return;
            }
        }

        if (const auto* e = event.getIf<sf::Event::KeyPressed>()) {
            if (handle_press(*e, b)) {
                return;
            }
        }

        if (const auto* e = event.getIf<sf::Event::KeyReleased>()) {
            if (handle_release(*e, b)) {
                return;
            }
        }
    }
}

bool Button::handle_press(const sf::Event::KeyPressed& event, Binding& b) {
    if (!b.matches(event)) {
        return false;
    }

    b.press();
    pressed_by_ = &b;
    state_      = State::Active;
    return true;
}

bool Button::handle_press(const sf::Event::MouseButtonPressed& event, Binding& b) {
    if (!b.matches(event)) {
        return false;
    }

    if (check_collision(event.position)) {
        b.press();
        pressed_by_ = &b;
        state_      = State::Active;
    }
    return true;
}

bool Button::handle_release(const sf::Event::KeyReleased& event, Binding& b) {
    if (!b.matches(event)) {
        return false;
    }

    if (b.is_pressed()) {
        b.invoke();
    }
    pressed_by_ = nullptr;
    b.release();

    if (state_ != State::Disabled) {
        state_ = State::Normal;
    }
    return true;
}

bool Button::handle_release(const sf::Event::MouseButtonReleased& event, Binding& b) {
    if (!b.matches(event)) {
        return false;
    }

    if (check_collision(event.position)) {
        if (b.is_pressed()) {
            b.invoke();
        }
        if (state_ != State::Disabled) {
            state_ = State::Hover;
        }
    } else {
        state_ = State::Normal;
    }
    b.release();
    pressed_by_ = nullptr;
    return true;
}

void Button::handle_mouse_move(const sf::Event::MouseMoved& e) {
    if (check_collision(e.position)) {
        if (state_ != State::Active) {
            state_ = State::Hover;
        }
    } else if (state_ != State::Active) {
        state_ = State::Normal;
    }
}

void Button::set_style(Style style) {
    style_ = style;
    update();
}

void Button::update() {
    if (pressed_by_) {
        state_ = State::Active;
    }

    switch (state_) {
    case State::Disabled: Label::set_style(style_.disabled); break;
    case State::Normal:   Label::set_style(style_.normal); break;
    case State::Hover:    Label::set_style(style_.hover); break;
    case State::Active:   Label::set_style(style_.active); break;
    }
}

} // namespace ui
