// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#include "ui/Label.hpp"

namespace ui {

Label::Label(
    const sf::Font&             font,
    sf::Vector2f                size,
    Style                       style,
    sf::String                  text,
    std::optional<unsigned int> font_size
) : bg_{size},
    fg_{font},
    pref_font_size_{font_size} {
    set_text(std::move(text));
    set_style(style);
}

Label::~Label() = default;

void Label::center_text() {
    const sf::FloatRect bg_bounds = bg_.getGlobalBounds();

    // Decrease the available space by padding value.
    const float max_width  = std::max(0.0f, bg_bounds.size.x - (RELATIVE_PADDING * 2 * bg_bounds.size.x) - OUTLINE_SIZE);
    const float max_height = std::max(0.0f, bg_bounds.size.y - (RELATIVE_PADDING * 2 * bg_bounds.size.y) - OUTLINE_SIZE);

    if (max_width <= 0.0f || max_height <= 0.0f) {
        return;
    }

    unsigned int font_size;

    if (!pref_font_size_ || *pref_font_size_ < 1) {
        font_size = static_cast<unsigned int>(max_height);
    } else {
        font_size = *pref_font_size_;
    }

    while (font_size > 1) {
        fg_.setCharacterSize(font_size);
        const sf::FloatRect fg_bounds = fg_.getLocalBounds();
        if (fg_bounds.size.x < max_width && fg_bounds.size.y < max_height) {
            break;
        }
        font_size--;
    }
    fg_.setCharacterSize(font_size);

    fg_.setOrigin(fg_.getLocalBounds().getCenter());
    fg_.setPosition(bg_bounds.getCenter());
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (visible_.bg) {
        target.draw(bg_, states);
    }
    if (visible_.fg) {
        target.draw(fg_, states);
    }
}

sf::FloatRect Label::get_bounds() const {
    return bg_.getGlobalBounds();
}

sf::Vector2f Label::get_position() const {
    return bg_.getPosition();
}

sf::Vector2f Label::get_size() const {
    return bg_.getSize();
}

void Label::handle_event([[maybe_unused]] const sf::Event& event) {
}

void Label::set_position(sf::Vector2f pos) {
    bg_.setPosition(pos);
    center_text();
}

void Label::set_style(Style style) {
    visible_.bg = style.bg.a > 0 || style.ol.a > 0;
    visible_.fg = style.fg.a > 0;

    bg_.setFillColor(style.bg);

    bg_.setOutlineColor(style.ol);

    if (style.ol.a > 0) {
        bg_.setOutlineThickness(OUTLINE_SIZE);
    } else {
        bg_.setOutlineThickness(0.0f);
    }

    fg_.setFillColor(style.fg);
}

void Label::set_text(sf::String text) {
    // Centering small, single-line text causes it to drift to the left.
    if (text.find(sf::String{"\n"}) != sf::String::InvalidPos) {
        fg_.setLineAlignment(sf::Text::LineAlignment::Center);
    } else {
        fg_.setLineAlignment(sf::Text::LineAlignment::Left);
    }

    fg_.setString(std::move(text));
    center_text();
}

} // namespace ui
