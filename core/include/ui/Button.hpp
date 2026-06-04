#pragma once

#include <functional>
#include <optional>
#include <string>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "ui/Binding.hpp"
#include "ui/Label.hpp"

namespace ui {

class Button : public Label {
public:
    struct Style {
        Label::Style disabled;
        Label::Style normal;
        Label::Style hover;
        Label::Style active;
    };

    // Constructs a new Button. If specified font_size is at least equal to 1,
    // the constructor will attempt to preserve it. If text does not fit
    // inside the Button, font size will be decreased.
    Button(
        const sf::Font&      font,
        sf::Vector2f         size,
        Style                style,
        std::string          text,
        std::optional<float> font_size = std::nullopt
    );

    virtual ~Button();

    // Binds keyboard key or a mouse button to callback.
    template <Bindable Input>
    void bind(Input activator, std::function<void()> callback) {
        bindings_.emplace_back(activator, std::move(callback));
    }

    // Makes the Button non-interactive.
    void disable() noexcept;

    // Restores interactivity to the Button instance.
    void enable() noexcept;

    // Handles an event passed down from the caller.
    void handle_event(const sf::Event& event) override;

    // Sets the style of the Button instance.
    void set_style(Style style);

    // Unbinds the specified key or mouse button. If it is not bound,
    // no modification occurs and no feedback is provided.
    template <Bindable Input>
    void unbind(Input activator) {
        for (auto it = bindings_.begin(); it != bindings_.end(); it++) {
            if (it->activated_by(activator)) {
                bindings_.erase(it);
                return;
            }
        }
    }

private:
    enum class State {
        // Not responding to user input.
        Disabled,

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
    Binding* pressed_by_;

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

} // namespace ui
