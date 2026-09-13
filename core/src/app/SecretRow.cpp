// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <cassert>

#include "app/SecretRow.hpp"

namespace app {

SecretRow::SecretRow(
    const sf::Font&  font,
    sf::Vector2f     size,
    lang::SecretRow  lang,
    theme::SecretRow theme
) : ui::Box{size, theme.box, ui::Layout::Type::RowLayout},
    game_state_{game::State::Running},
    lang_{lang},
    theme_{theme} {
    auto& code_box = add_component<ui::Box>(
        size.componentWiseMul(CODE_BOX_REL_SIZE),
        theme.code_box,
        ui::Layout::Type::RowLayout
    );

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
        theme.info_running,
        lang.info_running,
        static_cast<unsigned int>(size.y * INFO_FONT_REL_SIZE)
    );
}

SecretRow::~SecretRow() = default;

void SecretRow::display_code(std::span<const int, game::Row::ROW_LEN> code) {
    for (std::size_t i = 0; i < code.size(); i++) {
        code_buttons_[i]->set_value(code[i]);
        code_buttons_[i]->use_active_style();
    }
}

void SecretRow::display_info(game::State state) noexcept {
    game_state_ = state;
    update();
}

void SecretRow::reset() {
    for (auto b : code_buttons_) {
        b->reset();
    }
    display_info(game::State::Running);
}

void SecretRow::update() {
    switch (game_state_) {
    case game::State::Running:
        info_->set_text(lang_.info_running);
        info_->set_style(theme_.info_running);
        break;
    case game::State::Won:
        info_->set_text(lang_.info_won);
        info_->set_style(theme_.info_won);
        break;
    case game::State::Lost:
        info_->set_text(lang_.info_lost);
        info_->set_style(theme_.info_lost);
    }
}

} // namespace app
