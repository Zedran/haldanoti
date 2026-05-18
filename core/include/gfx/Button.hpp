#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "gfx/Binding.hpp"
#include "gfx/Label.hpp"

namespace gfx::ui {

class Button : public Label {
public:
    struct Style {
        Label::Style normal;
        Label::Style hover;
        Label::Style active;
    };

    Button(
        const sf::Font& font,
        sf::Vector2f    size,
        Style           style,
        std::string     text
    );

    virtual ~Button();

    // Binds keyboard key to callback.
    void bind(sf::Keyboard::Key key, Binding::Callback callback);

    // Binds mouse button to callback.
    void bind(sf::Mouse::Button button, Binding::Callback callback);

    // Handles an event passed down from the caller.
    void handle_event(const sf::Event& event) override;

private:
    enum class State {
        // Not clicked on, not hovered above.
        Normal,

        // Hovered above.
        Hover,

        // Clicked on.
        Active
    };

    // A container holding bound keys and mouse buttons.
    std::vector<Binding> bindings_;

    // Points to the Binding that "pressed" the Button. If pressed_by is not
    // null, the Button instance only listens to the events associated with
    // the Binding that "pressed" the Button. This prevents the Button from
    // responding to inputs from several bindings at once.
    Binding* pressed_by;

    State state_;

    Style style_;

    bool check_collision(sf::Vector2i pos);

    // A fragment of the handle_event procedure that processes
    // MouseButtonPressed events.
    bool handle_press(const sf::Event::MouseButtonPressed& event, Binding& button);

    // A fragment of the handle_event procedure that processes KeyPressed
    // events.
    bool handle_press(const sf::Event::KeyPressed& event, Binding& key);

    // A fragment of the handle_event procedure that processes
    // MouseButtonReleased events.
    bool handle_release(const sf::Event::MouseButtonReleased& event, Binding& button);

    // A fragment of the handle_event procedure that processes KeyReleased
    // events.
    bool handle_release(const sf::Event::KeyReleased& event, Binding& key);

    // A fragment of the handle_event procedure that processes mouse movement
    // events.
    void handle_mouse_move(const sf::Event::MouseMoved& e);

    // Updates graphical state of the Button instance.
    void update();
};

} // namespace gfx::ui
