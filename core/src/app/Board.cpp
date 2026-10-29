// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <cassert>
#include <utility>

#include "app/Board.hpp"
#include "app/CodeButton.hpp"
#include "app/GameRow.hpp"
#include "app/SecretRow.hpp"
#include "game/Game.hpp"
#include "ui/Box.hpp"
#include "utils/debug.hpp"

namespace app {

Board::Board(
    const sf::Font& font,
    sf::Vector2f    size,
    lang::Board     lang,
    theme::Board    theme,
    std::size_t     code_len,
    bool            code_chars,
    bool            fb_chars
) : ui::Box{size, theme.box, ui::Layout::Type::ColumnLayout},
    active_row_{},
    game_rows_(game::Game::NUM_ROWS) {
    GameRow::set_lang(std::move(lang.game_row));
    GameRow::set_theme(std::move(theme.game_row));
    CodeButton::set_show_text(code_chars);
    FeedbackLabel::set_show_text(fb_chars);

    secret_row_ = &add_component<SecretRow>(
        font,
        size.componentWiseMul(SecretRow::REL_SIZE),
        code_len,
        std::move(lang.secret_row),
        theme.secret_row
    );

    const sf::Vector2f gr_size = size.componentWiseMul(GameRow::REL_SIZE);

    for (std::size_t i = game::Game::NUM_ROWS; i > 0; i--) {
        GameRow* ptr = &add_component<GameRow>(
            font,
            gr_size,
            code_len,
            i
        );
        game_rows_[i - 1] = ptr;
    }

    game_rows_[active_row_]->unlock();
}

Board::~Board() = default;

void Board::allow_unique_only(bool v) noexcept {
    GameRow::allow_unique_only(v);
}

void Board::end_game(std::span<const int> good_code, game::State state) {
    assert(state != game::State::Running);
    assert(secret_row_);
    secret_row_->display_code(good_code);
    secret_row_->display_info(state);
}

GameRow& Board::get_active_row() const noexcept {
    assert(game_rows_[active_row_]);
    return *game_rows_[active_row_];
}

bool Board::is_last_row() const noexcept {
    return active_row_ == game_rows_.size() - 1;
}

void Board::next_row() {
    assert(!is_last_row());

    active_row_++;
    game_rows_[active_row_]->unlock();
}

void Board::reset() {
    dbg("--- BOARD RESET BEGINS ---");

    secret_row_->reset();

    for (auto& gr : game_rows_) {
        gr->reset();
    }

    active_row_ = 0;
    game_rows_[active_row_]->unlock();

    dbg("---  BOARD RESET ENDS  ---");
}

void Board::resize(std::size_t code_len) {
    for (auto& r : game_rows_) {
        r->resize(code_len);
    }
    secret_row_->resize(code_len);
}

void Board::set_hints(bool enabled, std::optional<std::size_t> hint) {
    secret_row_->set_hint(enabled, hint);
}

} // namespace app
