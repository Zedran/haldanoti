#include "gfx/Box.hpp"
#include "utils/utils.hpp"

namespace gfx::ui {

Box::Box(sf::Vector2f size, sf::Color bg_color, Layout::Type layout) : bg_{size} {
    bg_.setFillColor(bg_color);

    switch (layout) {
    case Layout::Type::ColumnLayout: layout_ = std::make_unique<ColumnLayout>(); break;
    case Layout::Type::RowLayout:    layout_ = std::make_unique<RowLayout>(); break;
    }
}

Box::~Box() = default;

void Box::add_component(std::unique_ptr<Widget> w) {
    components_.push_back(std::move(w));
}

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
    bg_.setPosition(utils::round(pos));
    layout_->place(bg_.getGlobalBounds(), components_);
}

} // namespace gfx::ui
