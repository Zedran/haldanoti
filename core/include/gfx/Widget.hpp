#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

namespace gfx::ui {

// Common interface for UI elements.
class Widget : public sf::Drawable, public sf::Transformable {
public:
    virtual ~Widget() = default;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

    virtual sf::Vector2f get_position() const = 0;

    virtual sf::Vector2f get_size() const = 0;

    virtual void handle_event(const sf::Event& event) = 0;

    virtual void set_position(sf::Vector2f pos) = 0;
};

} // namespace gfx::ui
