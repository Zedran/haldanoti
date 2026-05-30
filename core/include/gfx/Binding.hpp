#pragma once

#include <functional>
#include <variant>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace gfx::ui {

// Represents an action assigned to a key or mouse button.
class Binding {
public:
    using Callback = std::function<void()>;

    // Constructs a new Binding that responds to a key.
    Binding(Callback callback, sf::Keyboard::Key key);

    // Constructs a new Binding that responds to a mouse button.
    Binding(Callback callback, sf::Mouse::Button button);

    virtual ~Binding();

    // Returns true if the specified mouse button activates the Binding.
    bool activated_by(sf::Mouse::Button button) const noexcept;

    // Returns true if the specified key activates the Binding.
    bool activated_by(sf::Keyboard::Key key) const noexcept;

    // Calls the stored function.
    void invoke();

    // Returns true if the Binding is pressed.
    bool is_pressed() const noexcept;

    // Returns true if the bound key corresponds to the MouseButtonPressed
    // event.
    bool matches(const sf::Event::MouseButtonPressed& button) const;

    // Returns true if the bound key corresponds to the MouseButtonReleased
    // event.
    bool matches(const sf::Event::MouseButtonReleased& button) const;

    // Returns true if the bound key corresponds to the KeyPressed event.
    bool matches(const sf::Event::KeyPressed& key) const;

    // Returns true if the bound key corresponds to the KeyReleased event.
    bool matches(const sf::Event::KeyReleased& key) const;

    // To be called by controller when the assigned Binding is pressed.
    void press() noexcept;

    // To be called by controller when the assigned Binding is released.
    void release() noexcept;

private:
    Callback callback_;

    bool pressed_;

    // Stores the key or a mouse button that the Binding instance responds to.
    std::variant<sf::Keyboard::Key, sf::Mouse::Button> trigger_;

    // A wrapper for std::holds_alternative<sf::Keyboard::Key>().
    // It makes the overloaded ::matches member functions easier to read.
    bool bound_to_key() const noexcept;

    // A wrapper for std::holds_alternative<sf::Mouse::Button>().
    // It makes the overloaded ::matches member functions easier to read.
    bool bound_to_mouse() const noexcept;
};

} // namespace gfx::ui
