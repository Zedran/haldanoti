#include "app/Toolbar.hpp"
#include "ui/Button.hpp"

namespace app {

Toolbar::Toolbar(
    const sf::Font&       font,
    sf::Vector2f          size,
    theme::Toolbar        theme,
    std::function<void()> new_game_func,
    std::function<void()> exit_func
) : ui::Box{size, theme.box, ui::Layout::Type::RowLayout} {
    // Temporary fixed values for text size in buttons, depending on whether
    // it is split across two lines or is contained in a single line.
    // Multiline text positioning should be done properly before adding
    // customizable localization.
    constexpr float DOUBLE_LINE_REL_TEXT_SIZE{0.3f};
    constexpr float SINGLE_LINE_REL_TEXT_SIZE{0.4f};

    add_component<ui::Button>(
        font,
        sf::Vector2f{size.y * BUTTON_RELSIZE.x, size.y * BUTTON_RELSIZE.y},
        theme.new_game,
        " New\nGame",
        size.y * DOUBLE_LINE_REL_TEXT_SIZE
    )
        .bind(sf::Mouse::Button::Left, new_game_func);

    add_component<ui::Button>(
        font,
        sf::Vector2f{size.y * BUTTON_RELSIZE.x, size.y * BUTTON_RELSIZE.y},
        theme.exit,
        "Exit",
        size.y * SINGLE_LINE_REL_TEXT_SIZE
    )
        .bind(sf::Mouse::Button::Left, exit_func);
}

Toolbar::~Toolbar() = default;

} // namespace app
