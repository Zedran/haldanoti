// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <cassert>
#include <cstddef>
#include <string>

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

#include "app/CodeButton.hpp"
#include "app/FeedbackLabel.hpp"
#include "app/GameRow.hpp"
#include "game/Row.hpp"
#include "lang/GameRow.hpp"
#include "theme/GameRow.hpp"
#include "ui/Button.hpp"
#include "ui/Layout.hpp"
#include "utils/debug.hpp"

namespace app {

lang::GameRow GameRow::lang_{};

theme::GameRow GameRow::styles_{};

GameRow::GameRow(const sf::Font& font, sf::Vector2f size, int row_number)
    : ui::Box{size, styles_.box.inactive, ui::Layout::Type::RowLayout},
      locked_{}, row_num_{std::to_string(row_number)} {
    code_box_ = &add_component<ui::Box>(
        size.componentWiseMul(CODE_BOX_REL_SIZE),
        styles_.code_box.inactive,
        ui::Layout::Type::RowLayout
    );

    assert(styles_.code_button);
    CodeButton::set_theme(*styles_.code_button);

    const sf::Vector2f cb_size{
        size.y * CodeButton::REL_SIZE.x,
        size.y * CodeButton::REL_SIZE.y,
    };

    for (std::size_t i = 0; i < game::Row::ROW_LEN; i++) {
        auto* cb = &code_box_->add_component<CodeButton>(font, cb_size);
        code_buttons_.push_back(cb);
    }

    fb_box_ = &add_component<ui::Box>(
        size.componentWiseMul(FB_BOX_REL_SIZE),
        styles_.fb_box.inactive,
        ui::Layout::Type::RowLayout
    );

    FeedbackLabel::set_lang(lang_.fb_label);
    FeedbackLabel::set_theme(styles_.fb_label);

    const sf::Vector2f fbl_size{
        size.y * FeedbackLabel::REL_SIZE.x,
        size.y * FeedbackLabel::REL_SIZE.y,
    };

    for (std::size_t i = 0; i < game::Row::ROW_LEN; i++) {
        auto* fbl = &fb_box_->add_component<FeedbackLabel>(font, fbl_size);
        fb_labels_.push_back(fbl);
    }

    ok_box_ = &add_component<ui::Box>(
        size.componentWiseMul(OK_BOX_REL_SIZE),
        styles_.ok_box.inactive,
        ui::Layout::Type::RowLayout
    );

    ok_button_ = &ok_box_->add_component<ui::Button>(
        font,
        sf::Vector2f{
            size.y * OK_BUTTON_REL_SIZE.x,
            size.y * OK_BUTTON_REL_SIZE.y,
        },
        styles_.ok_button,
        "",
        static_cast<unsigned int>(size.y * OK_BUTTON_FONT_REL_SIZE)
    );
    ok_button_->bind(sf::Mouse::Button::Left, [this] { this->lock(true); });

    lock(false);
}

GameRow::~GameRow() = default;

bool GameRow::all_set() const noexcept {
    for (const auto& cb : code_buttons_) {
        if (!cb->is_set()) {
            return false;
        }
    }
    return true;
}

std::array<int, game::Row::ROW_LEN> GameRow::get_code() const noexcept {
    std::array<int, game::Row::ROW_LEN> code;

    for (std::size_t i = 0; i < code_buttons_.size(); i++) {
        code[i] = code_buttons_[i]->code_element();
    }
    return code;
}

bool GameRow::is_locked() const noexcept {
    return locked_;
}

void GameRow::lock(bool commit) {
    if (commit && !all_set()) {
        dbg("failed to commit row {}", row_num_.toAnsiString());
        return;
    }

    locked_ = true;

    for (auto& b : code_buttons_) {
        b->disable(commit);
    }
    ok_button_->set_text(row_num_);
    ok_button_->disable();

    update_box_styles();

    dbg("locked row {}: commit = {}", row_num_.toAnsiString(), commit);
}

void GameRow::reset() {
    for (std::size_t i = 0; i < game::Row::ROW_LEN; i++) {
        code_buttons_[i]->reset();
        fb_labels_[i]->reset();
    }
    lock(false);
}

void GameRow::set_feedback(game::Feedback fb) {
    assert(static_cast<std::size_t>(fb.red_count + fb.white_count) <= game::Row::ROW_LEN);

    for (std::size_t i = 0; i < static_cast<std::size_t>(fb.red_count); i++) {
        fb_labels_[i]->set_pin(FeedbackLabel::Pin::Red);
    }

    const std::size_t start_from = static_cast<std::size_t>(fb.red_count);

    for (std::size_t i = start_from; i < start_from + static_cast<std::size_t>(fb.white_count); i++) {
        fb_labels_[i]->set_pin(FeedbackLabel::Pin::White);
    }
}

void GameRow::set_lang(lang::GameRow lang) noexcept {
    lang_ = lang;
}

void GameRow::set_theme(theme::GameRow theme) noexcept {
    styles_ = theme;
}

void GameRow::unlock() {
    locked_ = false;

    for (auto& b : code_buttons_) {
        b->enable();
    }
    ok_button_->set_text(lang_.ok);
    ok_button_->enable();

    update_box_styles();

    dbg("unlocked row {}", row_num_.toAnsiString());
}

void GameRow::update_box_styles() {
    if (locked_) {
        set_style(styles_.box.inactive);
        code_box_->set_style(styles_.code_box.inactive);
        fb_box_->set_style(styles_.fb_box.inactive);
        ok_box_->set_style(styles_.ok_box.inactive);
    } else {
        set_style(styles_.box.active);
        code_box_->set_style(styles_.code_box.active);
        fb_box_->set_style(styles_.fb_box.active);
        ok_box_->set_style(styles_.ok_box.active);
    }
}

} // namespace app
