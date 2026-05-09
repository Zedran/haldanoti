#include "gfx/Button.hpp"
#include "utils/utils.hpp"

namespace gfx::ui {

Button::Button(
    const sf::Font& font,
    sf::Vector2f    size,
    std::string     fg_color,
    std::string     bg_color_normal,
    std::string     bg_color_hover,
    std::string     bg_color_active,
    std::string     text,
    Callback        callback
) : Label{font, size, fg_color, bg_color_normal, text},
    bg_color_normal_{utils::decode_color(bg_color_normal)},
    bg_color_hover_{utils::decode_color(bg_color_hover)},
    bg_color_active_{utils::decode_color(bg_color_active)},
    callback_{callback},
    state_{State::Normal} {
}

Button::~Button() = default;

bool Button::check_collision(sf::Vector2i pos) {
    return check_collision(static_cast<sf::Vector2f>(pos));
}

bool Button::check_collision(sf::Vector2f pos) {
    return utils::detect_collision(get_bounds(), pos);
}

void Button::handle_event(const sf::Event& event) {
    if (const auto* e = event.getIf<sf::Event::MouseButtonPressed>()) {
        handle_lmb_press(*e);
    } else if (const auto* e = event.getIf<sf::Event::MouseButtonReleased>()) {
        handle_lmb_release(*e);
    } else if (const auto* e = event.getIf<sf::Event::MouseMoved>()) {
        handle_mouse_move(*e);
    } else {
        return;
    }
    update();
}

void Button::handle_lmb_press(const sf::Event::MouseButtonPressed& e) {
    if (e.button != sf::Mouse::Button::Left) {
        return;
    }

    if (check_collision(e.position)) {
        state_ = State::Active;
    }
}

void Button::handle_lmb_release(const sf::Event::MouseButtonReleased& e) {
    if (e.button != sf::Mouse::Button::Left) {
        return;
    }

    if (check_collision(e.position)) {
        if (state_ == State::Active) {
            invoke();
        }
        state_ = State::Hover;
    } else {
        state_ = State::Normal;
    }
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

void Button::invoke() {
    if (callback_) {
        callback_();
    }
}

void Button::update() {
    switch (state_) {
    case State::Normal: set_bg_color(bg_color_normal_); break;
    case State::Hover:  set_bg_color(bg_color_hover_); break;
    case State::Active: set_bg_color(bg_color_active_); break;
    }
}

} // namespace gfx::ui
