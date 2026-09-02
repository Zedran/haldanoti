// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include "ui/Blank.hpp"

namespace ui {

Blank::Blank(sf::Vector2f size) : shape_{{}, size} {}

Blank::~Blank() = default;

void Blank::draw([[maybe_unused]] sf::RenderTarget& target, [[maybe_unused]] sf::RenderStates states) const {
}

sf::Vector2f Blank::get_position() const {
    return shape_.position;
}

sf::Vector2f Blank::get_size() const {
    return shape_.size;
}

void Blank::handle_event([[maybe_unused]] const sf::Event& event) {
}

void Blank::set_position(sf::Vector2f pos) {
    shape_.position = pos;
}

} // namespace ui
