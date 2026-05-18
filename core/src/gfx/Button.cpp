#include "gfx/Button.hpp"
#include "gfx/Binding.hpp"
#include "utils/FinalAction.hpp"
#include "utils/utils.hpp"

namespace gfx::ui {

Button::Button(
    const sf::Font& font,
    sf::Vector2f    size,
    Style           style,
    std::string     text
) : Label{font, size, style.normal, text},
    pressed_by{},
    state_{State::Normal},
    style_{style} {}

Button::~Button() = default;

void Button::bind(sf::Mouse::Button button, Binding::Callback callback) {
    bindings_.emplace_back(std::move(callback), button);
}

void Button::bind(sf::Keyboard::Key key, Binding::Callback callback) {
    bindings_.emplace_back(std::move(callback), key);
}

bool Button::check_collision(sf::Vector2i pos) {
    return utils::detect_collision(get_bounds(), pos);
}

void Button::handle_event(const sf::Event& event) {
    const auto update = utils::finally([this] { this->update(); });

    if (const auto* e = event.getIf<sf::Event::MouseMoved>()) {
        handle_mouse_move(*e);
        return;
    }

    if (pressed_by) {
        if (const auto* e = event.getIf<sf::Event::MouseButtonReleased>()) {
            if (handle_release(*e, *pressed_by)) {
                return;
            }
        }

        if (const auto* e = event.getIf<sf::Event::KeyReleased>()) {
            handle_release(*e, *pressed_by);
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
    pressed_by = &b;
    state_     = State::Active;
    return true;
}

bool Button::handle_press(const sf::Event::MouseButtonPressed& event, Binding& b) {
    if (!b.matches(event)) {
        return false;
    }

    if (check_collision(event.position)) {
        b.press();
        pressed_by = &b;
        state_     = State::Active;
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
    state_     = State::Normal;
    pressed_by = nullptr;
    b.release();
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
        state_ = State::Hover;
    } else {
        state_ = State::Normal;
    }
    b.release();
    pressed_by = nullptr;
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

void Button::update() {
    if (pressed_by) {
        state_ = State::Active;
    }

    switch (state_) {
    case State::Normal: set_style(style_.normal); break;
    case State::Hover:  set_style(style_.hover); break;
    case State::Active: set_style(style_.active); break;
    }
}

} // namespace gfx::ui
