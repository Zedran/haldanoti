#pragma once

#include <optional>
#include <string>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>

#include "gfx/Widget.hpp"

namespace ui {

class Label : public Widget {
public:
    struct Style {
        sf::Color bg;
        sf::Color fg;
    };

    // Constructs a new Label. If specified font_size is at least equal to 1,
    // the constructor will attempt to preserve it. If text does not fit
    // inside the Label, font size will be decreased.
    Label(
        const sf::Font&      font,
        sf::Vector2f         size,
        Style                style,
        std::string          text,
        std::optional<float> font_size = std::nullopt
    );

    virtual ~Label();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::FloatRect get_bounds() const;

    sf::Vector2f get_position() const override;

    sf::Vector2f get_size() const override;

    void handle_event(const sf::Event& event) override;

    void set_position(sf::Vector2f pos) override;

    void set_style(Style style);

    void set_text(std::string text);

private:
    // Padding value for text contained within every Label-derived type.
    static constexpr float RELATIVE_PADDING{0.05f};

    sf::RectangleShape bg_;
    sf::Text           fg_;

    // Preferred font size.
    std::optional<float> pref_font_size_;

    void center_text();
};

} // namespace ui
