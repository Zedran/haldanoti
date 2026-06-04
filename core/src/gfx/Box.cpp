#include "gfx/Box.hpp"

namespace ui {

Box::Box(sf::Vector2f size, Style style, Layout::Type layout) : bg_{size}, layout_{make_layout(layout)} {
    set_style(style);
}

Box::~Box() = default;

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(bg_, states);
    for (const auto& c : components_) {
        target.draw(*c, states);
    }
}

sf::Vector2f Box::get_position() const {
    return bg_.getPosition();
}

sf::Vector2f Box::get_size() const {
    return bg_.getSize();
}

void Box::handle_event(const sf::Event& event) {
    for (const auto& c : components_) {
        c->handle_event(event);
    }
}

void Box::set_position(sf::Vector2f pos) {
    bg_.setPosition(pos);
    layout_->place(bg_.getGlobalBounds(), components_);
}

void Box::set_style(Style style) {
    bg_.setFillColor(style.bg);
}

} // namespace ui
