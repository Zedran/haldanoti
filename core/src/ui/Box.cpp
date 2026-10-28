// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include "ui/Box.hpp"

namespace ui {

Box::Box(sf::Vector2f size, Style style, Layout::Type layout) : bg_{size}, layout_{make_layout(layout)} {
    set_style(style);
}

Box::~Box() = default;

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (visible_.bg) {
        target.draw(bg_, states);
    }

    for (const auto& c : components_) {
        target.draw(*c, states);
    }
}

const Widget& Box::get_component(std::size_t index) const {
    return *components_.at(index);
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

void Box::pop_component() noexcept {
    components_.pop_back();
}

void Box::set_position(sf::Vector2f pos) {
    bg_.setPosition(pos);
    layout_->place(bg_.getGlobalBounds(), components_);
}

void Box::set_style(Style style) {
    visible_.bg = style.bg.a > 0 || style.ol.a > 0;

    bg_.setFillColor(style.bg);

    bg_.setOutlineColor(style.ol);

    if (style.ol.a > 0) {
        bg_.setOutlineThickness(OUTLINE_SIZE);
    } else {
        bg_.setOutlineThickness(0.0f);
    }
}

} // namespace ui
