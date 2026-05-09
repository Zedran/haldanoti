#include <cmath>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#include "gfx/Label.hpp"
#include "utils/utils.hpp"

namespace gfx ::ui {

Label::Label(
    const sf::Font& font,
    sf::Vector2f    size,
    std::string     fg_color,
    std::string     bg_color,
    std::string     text
) : bg_{size},
    fg_{font, std::move(text)} {
    set_bg_color(bg_color);
    set_fg_color(fg_color);
}

Label::~Label() = default;

void Label::center_text() {
    const sf::FloatRect bg_bounds = bg_.getGlobalBounds();

    // Decrease the available space by padding value.
    const float max_width  = std::max(0.0f, std::round(bg_bounds.size.x - (RELATIVE_PADDING * 2 * bg_bounds.size.x)));
    const float max_height = std::max(0.0f, std::round(bg_bounds.size.y - (RELATIVE_PADDING * 2 * bg_bounds.size.y)));

    if (max_width <= 0.0f || max_height <= 0.0f) {
        return;
    }

    // Initial estimate.
    float font_size = max_height;

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

void Label::set_bg_color(sf::Color c) {
    bg_.setFillColor(c);
}

void Label::set_bg_color(std::string c_hex) {
    set_bg_color(utils::decode_color(std::move(c_hex)));
}

void Label::set_fg_color(sf::Color c) {
    fg_.setFillColor(c);
}

void Label::set_fg_color(std::string c_hex) {
    set_fg_color(utils::decode_color(std::move(c_hex)));
}

void Label::set_position(sf::Vector2f pos) {
    bg_.setPosition(utils::round(pos));
    center_text();
}

void Label::set_text(std::string text) {
    fg_.setString(text);
    center_text();
}

} // namespace gfx::ui
