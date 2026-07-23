#include <cassert>

#include "app/Board.hpp"
#include "app/GameRow.hpp"
#include "app/SecretRow.hpp"
#include "game/Game.hpp"
#include "ui/Box.hpp"
#include "utils/debug.hpp"

namespace app {

Board::Board(const sf::Font& font, sf::Vector2f size, theme::Board theme)
    : ui::Box{size, theme.box, ui::Layout::Type::ColumnLayout}, active_row_{}, game_rows_(game::Game::NUM_ROWS) {
    secret_row_ = &add_component<SecretRow>(
        font,
        size.componentWiseMul(SecretRow::REL_SIZE),
        theme.secret_row
    );

    GameRow::set_theme(theme.game_row);

    for (std::size_t i = game::Game::NUM_ROWS; i > 0; i--) {
        GameRow* ptr = &add_component<GameRow>(
            font,
            size.componentWiseMul(GameRow::REL_SIZE),
            i
        );
        game_rows_[i - 1] = ptr;
    }
}

Board::~Board() = default;

void Board::end_game(std::span<const int, game::Row::ROW_LEN> good_code, game::State state) {
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

} // namespace app
