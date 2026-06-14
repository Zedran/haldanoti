#include <cassert>

#include "app/SecretRow.hpp"

namespace app {

SecretRow::SecretRow(const sf::Font& font, sf::Vector2f size, theme::SecretRow theme)
    : ui::Box{size, theme.box, ui::Layout::Type::RowLayout}, theme_{theme} {
    auto& code_box = add_component<ui::Box>(
        size.componentWiseMul(CODE_BOX_REL_SIZE),
        theme.code_box,
        ui::Layout::Type::RowLayout
    );

    assert(theme.code_button);
    CodeButton::set_theme(*theme.code_button);

    const sf::Vector2f button_size{
        size.y * CodeButton::REL_SIZE.x,
        size.y * CodeButton::REL_SIZE.y,
    };

    for (std::size_t i = 0; i < game::Row::ROW_LEN; i++) {
        CodeButton& cb = code_box.add_component<CodeButton>(font, button_size);
        cb.unbind(sf::Mouse::Button::Left);
        cb.unbind(sf::Mouse::Button::Right);
        code_buttons_.push_back(&cb);
    }

    info_ = &add_component<ui::Label>(
        font,
        size.componentWiseMul(INFO_BOX_REL_SIZE),
        theme.info_won,
        "Info",
        size.y * INFO_FONT_REL_SIZE
    );

    display_info(Info::None);
}

SecretRow::~SecretRow() = default;

void SecretRow::display_code(std::span<const int, game::Row::ROW_LEN> code) {
    for (std::size_t i = 0; i < code.size(); i++) {
        code_buttons_[i]->set_value(code[i]);
        code_buttons_[i]->use_active_style();
    }
}

void SecretRow::display_info(Info info) noexcept {
    switch (info) {
    case Info::None:
        info_->set_text("");
        info_->set_style(theme_.info_none);
        break;
    case Info::Won:
        info_->set_text("Code correct");
        info_->set_style(theme_.info_won);
        break;
    case Info::Lost:
        info_->set_text("Game over");
        info_->set_style(theme_.info_lost);
    }
}

void SecretRow::reset() {
    for (auto b : code_buttons_) {
        b->reset();
    }
    display_info(Info::None);
}

} // namespace app
