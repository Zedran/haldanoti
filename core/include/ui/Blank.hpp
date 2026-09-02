// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include "ui/Widget.hpp"

namespace ui {

// An interface element that is not displayed and only provides spacing
// in the Box it belongs to.
class Blank : public Widget {
public:
    Blank(sf::Vector2f size);

    virtual ~Blank();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    virtual sf::Vector2f get_position() const override;

    virtual sf::Vector2f get_size() const override;

    virtual void handle_event(const sf::Event& event) override;

    virtual void set_position(sf::Vector2f pos) override;

private:
    sf::FloatRect shape_;
};

} // namespace ui
