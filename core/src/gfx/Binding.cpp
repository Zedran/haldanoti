#include "gfx/Binding.hpp"

namespace gfx::ui {

Binding::~Binding() = default;

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
    return activated_by(button.button);
}

bool Binding::matches(const sf::Event::MouseButtonReleased& button) const {
    return activated_by(button.button);
}

bool Binding::matches(const sf::Event::KeyPressed& key) const {
    return activated_by(key.code);
}

bool Binding::matches(const sf::Event::KeyReleased& key) const {
    return activated_by(key.code);
}

void Binding::press() noexcept {
    pressed_ = true;
}

void Binding::release() noexcept {
    pressed_ = false;
}

} // namespace gfx::ui
