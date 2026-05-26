#include "gfx/Binding.hpp"

namespace gfx::ui {

Binding::Binding(Callback callback, sf::Keyboard::Key key) : callback_{callback}, pressed_{}, trigger_{key} {}

Binding::Binding(Callback callback, sf::Mouse::Button button) : callback_{callback}, pressed_{}, trigger_{button} {}

Binding::~Binding() = default;

bool Binding::bound_to_key() const noexcept {
    return std::holds_alternative<sf::Keyboard::Key>(trigger_);
}

bool Binding::bound_to_mouse() const noexcept {
    return std::holds_alternative<sf::Mouse::Button>(trigger_);
}

void Binding::invoke() {
    if (callback_) {
        callback_();
    }
    pressed_ = false;
}

bool Binding::is_pressed() const noexcept {
    return pressed_;
}

bool Binding::matches(const sf::Event::MouseButtonPressed& button) const {
    return bound_to_mouse() && button.button == std::get<sf::Mouse::Button>(trigger_);
}

bool Binding::matches(const sf::Event::MouseButtonReleased& button) const {
    return bound_to_mouse() && button.button == std::get<sf::Mouse::Button>(trigger_);
}

bool Binding::matches(const sf::Event::KeyPressed& key) const {
    return bound_to_key() && key.code == std::get<sf::Keyboard::Key>(trigger_);
}

bool Binding::matches(const sf::Event::KeyReleased& key) const {
    return bound_to_key() && key.code == std::get<sf::Keyboard::Key>(trigger_);
}

void Binding::press() noexcept {
    pressed_ = true;
}

void Binding::release() noexcept {
    pressed_ = false;
}

} // namespace gfx::ui
