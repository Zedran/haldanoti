// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <cassert>

#include "game/Game.hpp"
#include "game/Row.hpp"

namespace game {

Game::Game(bool unique_elems)
    : active_row_num_{},
      rand_{Game::SCORE_MIN, Game::SCORE_MAX},
      rows_{},
      unique_elems_{unique_elems} {
    generate_code();
}

Game::Game(bool unique_elems, const unsigned long seed)
    : active_row_num_{},
      rand_{Game::SCORE_MIN, Game::SCORE_MAX, seed},
      rows_{},
      unique_elems_{unique_elems} {
    generate_code();
}

Game::~Game() = default;

std::size_t Game::active_row_num() const noexcept {
    return active_row_num_;
}

const Row& Game::active_row() const noexcept {
    assert(within_bounds());
    return rows_[active_row_num_];
}

Row& Game::active_row_mut() noexcept {
    assert(within_bounds());
    return rows_[active_row_num_];
}

void Game::advance() noexcept {
    assert(within_bounds());
    assert(!last_row());
    active_row_num_++;
}

void Game::allow_unique_only(bool v) noexcept {
    unique_elems_ = v;
}

void Game::generate_code() noexcept {
    if (unique_elems_) {
        rand_.read_unique(good_code_);
    } else {
        rand_.read(good_code_);
    }
}

std::span<const int> Game::good_code() const noexcept {
    return good_code_;
}

bool Game::last_row() const noexcept {
    return active_row_num_ == rows_.size() - 1;
}

void Game::reset() noexcept {
    active_row_num_ = 0;
    for (auto& r : rows_) {
        r.reset();
    }
    generate_code();
}

State Game::state() const noexcept {
    const Row& cur_row = active_row();

    if (!cur_row.locked()) {
        return State::Running;
    }

    if (cur_row.feedback().red_count == Row::ROW_LEN) {
        return State::Won;
    }

    if (last_row()) {
        return State::Lost;
    }

    return State::Running;
}

void Game::submit_code(std::span<const int> guess) noexcept {
    for ([[maybe_unused]] const auto& e : guess) {
        assert(e >= SCORE_MIN);
        assert(e <= SCORE_MAX);
    }
    active_row_mut().commit(good_code_, guess);
}

bool Game::within_bounds() const noexcept {
    return active_row_num_ < rows_.size();
}

} // namespace game
