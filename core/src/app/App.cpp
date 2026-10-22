// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <utility>

#include "app/App.hpp"
#include "app/Board.hpp"
#include "app/GameRow.hpp"
#include "app/Settings.hpp"
#include "app/UserInterface.hpp"
#include "config/Config.hpp"
#include "game/Feedback.hpp"
#include "game/State.hpp"
#include "utils/debug.hpp"
#include "utils/utils.hpp"

namespace app {

App::App(
    sf::Vector2f   window_size,
    config::Config conf,
    lang::Lang     lang,
    theme::Theme   theme,
    sf::String     version
) : game_{conf.unique_elems},
    ui_{window_size, conf, std::move(lang), std::move(theme), std::move(version)},
    window_{window_size, conf.vsync} {
    configure_hints(conf);

    [[maybe_unused]] const auto gc = game_.good_code();
    dbg("secret code {} {} {} {}", gc[0], gc[1], gc[2], gc[3]);
}

App::~App() = default;

void App::apply_config(const config::Config& c) {
    configure_hints(c);
    game_.allow_unique_only(c.unique_elems);
    window_.set_vsync(c.vsync);
}

void App::close() {
    window_.close();
}

void App::configure_hints(const config::Config& c) {
    if (c.hints) {
        ui_.set_hints(utils::count_distinct(game_.good_code()));
    } else {
        ui_.set_hints(std::nullopt);
    }
}

void App::new_game() {
    ui_.reset();
    game_.reset();

    configure_hints(ui_.get_settings().get_ref_config());

    [[maybe_unused]] const auto gc = game_.good_code();
    dbg("secret code {} {} {} {}", gc[0], gc[1], gc[2], gc[3]);
}

void App::poll_events() {
    while (const std::optional event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            close();
            break;
        }
        ui_.handle_event(*event);
    }
}

void App::run() {
    dbg("--- MAIN LOOP BEGINS ---");

    while (window_.isOpen()) {
        poll_events();
        tick();
        ui_.draw(window_);
    }

    dbg("---  MAIN LOOP ENDS  ---");
}

void App::save_config() {
    dbg("saving configuration");

    Settings& settings = ui_.get_settings();

    const config::Config c = settings.get_config();

    if (settings.config_differs(c)) {
        dbg("config modified");
        if (settings.restart_required(c)) {
            ui_.show_message(Message::Content::RestartRequired);
        }

        const bool grr = settings.game_reset_required(c);

        apply_config(c);
        config::write_config(settings.get_config());
        settings.set_ref_config(c);

        if (grr) {
            dbg("starting new game to apply settings");
            new_game();
        }
    }
}

void App::tick() {
    ui_.update();

    using Signal = UserInterface::Signal;

    switch (ui_.emit_signal()) {
    case Signal::None:
        break;
    case Signal::SaveConfig:
        save_config();
        return;
    case Signal::NewGame:
        new_game();
        return;
    case Signal::Exit:
        close();
        return;
    }

    Board& board = ui_.get_board();

    if (game_.state() != game::State::Running || !board.get_active_row().is_locked()) {
        return;
    }

    game_.submit_code(board.get_active_row().get_code());

    const game::Feedback fb = game_.active_row().feedback();
    dbg("feedback: red = {}, white = {}", fb.red_count, fb.white_count);

    board.get_active_row().set_feedback(fb);

    const game::State state = game_.state();

    if (state != game::State::Running || game_.last_row()) {
        dbg("GAME OVER");
        board.get_active_row().lock(true);
        board.end_game(game_.good_code(), state);
        return;
    }

    game_.advance();
    board.next_row();
}

} // namespace app
