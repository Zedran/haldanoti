#pragma once

#include <functional>
#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "gfx/Label.hpp"

namespace gfx::ui {

class Button : public Label {
public:
    using Callback = std::function<void()>;

    Button(
        const sf::Font& font,
        sf::Vector2f    size,
        std::string     fg_color,
        std::string     bg_color_normal,
        std::string     bg_color_hover,
        std::string     bg_color_active,
        std::string     text,
        Callback        callback = {}
    );

    virtual ~Button();

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

    sf::Color bg_color_normal_;
    sf::Color bg_color_hover_;
    sf::Color bg_color_active_;

    Callback callback_;

    State state_;

    bool check_collision(sf::Vector2i pos);

    bool check_collision(sf::Vector2f pos);

    void handle_lmb_press(const sf::Event::MouseButtonPressed& e);

    void handle_lmb_release(const sf::Event::MouseButtonReleased& e);

    void handle_mouse_move(const sf::Event::MouseMoved& e);

    void invoke();

    void update();
};

} // namespace gfx::ui
