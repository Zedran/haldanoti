// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <cmath>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#include "ui/Label.hpp"
#include "utils/utils.hpp"

namespace ui {

Label::Label(
    const sf::Font&      font,
    sf::Vector2f         size,
    Style                style,
    sf::String           text,
    std::optional<float> font_size
) : bg_{size},
    fg_{font, std::move(text)},
    pref_font_size_{font_size} {
    set_style(style);
}

Label::~Label() = default;

void Label::center_text() {
    const sf::FloatRect bg_bounds = bg_.getGlobalBounds();

    // Decrease the available space by padding value.
    const float max_width  = std::max(0.0f, std::round(bg_bounds.size.x - (RELATIVE_PADDING * 2 * bg_bounds.size.x) - OUTLINE_SIZE));
    const float max_height = std::max(0.0f, std::round(bg_bounds.size.y - (RELATIVE_PADDING * 2 * bg_bounds.size.y) - OUTLINE_SIZE));

    if (max_width <= 0.0f || max_height <= 0.0f) {
        return;
    }

    float font_size;

    if (!pref_font_size_ || *pref_font_size_ < 1.0f) {
        font_size = max_height;
    } else {
        font_size = *pref_font_size_;
    }

    while (font_size > 1.0f) {
        fg_.setCharacterSize(static_cast<unsigned int>(font_size));
        const sf::FloatRect fg_bounds = fg_.getLocalBounds();
        if (fg_bounds.size.x <= max_width && fg_bounds.size.y <= max_height) {
            break;
        }
        font_size -= 1.0f;
    }
    fg_.setCharacterSize(static_cast<unsigned int>(font_size));

    const sf::FloatRect fg_bounds = fg_.getLocalBounds();

    fg_.setOrigin(utils::round({
        fg_bounds.position.x + fg_bounds.size.x / 2.0f,
        fg_bounds.position.y + fg_bounds.size.y / 2.0f,
    }));

    fg_.setPosition(utils::round({
        bg_bounds.position.x + bg_bounds.size.x / 2.0f,
        bg_bounds.position.y + bg_bounds.size.y / 2.0f,
    }));
}

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(bg_, states);
    target.draw(fg_, states);
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
    bg_.setPosition(utils::round(pos));
    center_text();
}

void Label::set_style(Style style) {
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
    fg_.setString(text);
    center_text();
}

} // namespace ui
