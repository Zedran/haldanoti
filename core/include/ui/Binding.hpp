#pragma once

#include <functional>
#include <variant>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace ui {

// A common constraint for template functions that accept SFML enum values
// representing keys and mouse buttons.
template <typename Input>
concept Bindable =
    std::is_same_v<Input, sf::Keyboard::Key> ||
    std::is_same_v<Input, sf::Mouse::Button>;

// Constraint for SFML events related to keyboard buttons.
template <typename Event>
concept KeyboardInputEvent =
    std::is_same_v<Event, sf::Event::KeyPressed> ||
    std::is_same_v<Event, sf::Event::KeyReleased>;

// Constraint for SFML events related to mouse buttons.
template <typename Event>
concept MouseButtonInputEvent =
    std::is_same_v<Event, sf::Event::MouseButtonPressed> ||
    std::is_same_v<Event, sf::Event::MouseButtonReleased>;

// A common constraint for SFML input events that are processed by Binding.
template <typename Event>
concept InputEvent =
    KeyboardInputEvent<Event> ||
    MouseButtonInputEvent<Event>;

// Represents an action assigned to a key or mouse button.
class Binding {
public:
    // Constructs a new Binding that responds to the specified activator.
    template <Bindable Input>
    Binding(Input activator, std::function<void()> callback)
        : activator_{activator}, callback_{std::move(callback)}, pressed_{} {}

    virtual ~Binding();

    // Returns true if the specified key or mouse button activates the Binding.
    template <Bindable Input>
    bool activated_by(Input activator) const noexcept {
        return std::holds_alternative<Input>(activator_) && activator == std::get<Input>(activator_);
    }

    // Calls the stored function.
    void invoke();

    // Returns true if the Binding is pressed.
    bool is_pressed() const noexcept;

    // Returns true if the bound activator corresponds to the event.
    template <InputEvent Event>
    bool matches(const Event& event) const noexcept {
        if constexpr (KeyboardInputEvent<Event>) {
            return activated_by(event.code);
        }

        if constexpr (MouseButtonInputEvent<Event>) {
            return activated_by(event.button);
        }
    }

    // To be called by controller when the assigned Binding is pressed.
    void press() noexcept;

    // To be called by controller when the assigned Binding is released.
    void release() noexcept;

private:
    // Stores the key or a mouse button that the Binding instance responds to.
    std::variant<sf::Keyboard::Key, sf::Mouse::Button> activator_;

    std::function<void()> callback_;

    bool pressed_;
};

} // namespace ui
