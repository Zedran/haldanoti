// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <optional>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

#include "ui/Widget.hpp"

namespace ui {

class Label : public Widget {
public:
    struct Style {
        sf::Color bg;
        sf::Color fg;
        sf::Color ol;
    };

    // Constructs a new Label. If specified font_size is at least equal to 1,
    // the constructor will attempt to preserve it. If text does not fit
    // inside the Label, font size will be decreased.
    Label(
        const sf::Font&             font,
        sf::Vector2f                size,
        Style                       style,
        sf::String                  text,
        std::optional<unsigned int> font_size = std::nullopt
    );

    virtual ~Label();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::FloatRect get_bounds() const;

    sf::Vector2f get_position() const override;

    sf::Vector2f get_size() const override;

    void handle_event(const sf::Event& event) override;

    void set_position(sf::Vector2f pos) override;

    void set_style(Style style);

    void set_text(sf::String text);

private:
    // This struct holds information on whether individual visual elements
    // are visible. Each time set_style is called, colors of the new Style
    // are evaluated in regards to their alpha value. The ones with alpha
    // value of 0 are not drawn. This evaluation reduces the amount of
    // unnecessary calls to RenderTarget::draw.
    struct Visible {
        bool bg;
        bool fg;
    };

    // Outline size in pixels.
    static constexpr float OUTLINE_SIZE{1.0f};

    // Padding value for text contained within every Label-derived type.
    static constexpr float RELATIVE_PADDING{0.09f};

    sf::RectangleShape bg_;
    sf::Text           fg_;

    // Preferred font size.
    std::optional<unsigned int> pref_font_size_;

    Visible visible_;

    void center_text();
};

} // namespace ui
