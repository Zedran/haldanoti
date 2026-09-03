// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <cstdlib>

#include "app/App.hpp"
#include "app/Board.hpp"
#include "app/GameRow.hpp"
#include "app/Settings.hpp"
#include "app/Toolbar.hpp"
#include "config/Config.hpp"
#include "game/Feedback.hpp"
#include "game/State.hpp"
#include "utils/assets.hpp"
#include "utils/debug.hpp"

namespace app {

App::App(
    const sf::Font& font,
    sf::Image       icon,
    sf::Vector2f    window_size,
    config::Config  conf,
    lang::Lang      lang,
    theme::Theme    theme
) : bg_{theme.bg},
    board_{font, window_size.componentWiseMul(Board::REL_SIZE), lang.board, theme.board},
    game_{conf.unique_elems},
    scene_{Scene::Game},
    settings_{
        font,
        window_size,
        lang.settings,
        theme.settings,
        utils::get_lang_fnames()
    },
    toolbar_{
        font,
        window_size.componentWiseMul(Toolbar::REL_SIZE),
        lang.toolbar,
        theme.toolbar,
        [this] { this->new_game(); },
        [this] { this->set_scene(Scene::Settings); },
        [this] { this->close(); }
    },
    window_{sf::VideoMode(static_cast<sf::Vector2u>(window_size)), "mm", sf::Style::Close} {
    window_.setIcon(std::move(icon));
    window_.setVerticalSyncEnabled(true);

    dbg("screen_size = {{{:.0f}, {:.0f}}}", window_size.x, window_size.y);

    board_.set_position(sf::Vector2f{
        (1 - Board::REL_SIZE.x) / 2 * window_size.x,
        (1 - Board::REL_SIZE.y - Toolbar::REL_SIZE.y) / 2 * window_size.y,
    });
    toolbar_.set_position(sf::Vector2f{0.0f, (1.0f - Toolbar::REL_SIZE.y) * window_size.y});

    settings_.set_position({0.0f, 0.0f});
    settings_.set_config(conf);

    new_game();
}

App::~App() = default;

void App::close() {
    window_.close();
}

void App::draw() {
    window_.clear(bg_);

    window_.draw(board_);
    window_.draw(toolbar_);

    if (scene_ == Scene::Settings) {
        window_.draw(settings_);
    }

    window_.display();
}

void App::new_game() {
    board_.reset();
    game_.reset();

    [[maybe_unused]] const auto gc = game_.good_code();
    dbg("secret code {} {} {} {}", gc[0], gc[1], gc[2], gc[3]);
}

void App::poll_events() {
    while (const std::optional event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            close();
            break;
        }

        switch (scene_) {
        case Scene::Game:
            board_.handle_event(*event);
            toolbar_.handle_event(*event);
            break;
        case Scene::Settings:
            settings_.handle_event(*event);
        }
    }
}

int App::run() {
    dbg("--- MAIN LOOP BEGINS ---");

    while (window_.isOpen()) {
        poll_events();
        tick();
        draw();
    }

    dbg("---  MAIN LOOP ENDS  ---");
    return EXIT_SUCCESS;
}

void App::save_config() const {
    dbg("saving configuration");
    config::write_config(settings_.get_config());
}

void App::set_scene(Scene scene) noexcept {
    dbg("setting scene {}", static_cast<int>(scene));

    scene_ = scene;

    if (scene == Scene::Settings) {
        settings_.set_state(Settings::State::Running);
    }
}

void App::tick() {
    if (scene_ == Scene::Settings) {
        switch (settings_.get_state()) {
        case Settings::State::Running:
            break;
        case Settings::State::SaveAndClose:
            save_config();
            set_scene(Scene::Game);
            break;
        case Settings::State::Close:
            set_scene(Scene::Game);
            break;
        }
    }

    if (game_.state() != game::State::Running || !board_.get_active_row().is_locked()) {
        return;
    }

    game_.submit_code(board_.get_active_row().get_code());

    const game::Feedback fb = game_.active_row().feedback();
    dbg("feedback: red = {}, white = {}", fb.red_count, fb.white_count);

    board_.get_active_row().set_feedback(fb);

    const game::State state = game_.state();

    if (state != game::State::Running || game_.last_row()) {
        dbg("GAME OVER");
        board_.get_active_row().lock(true);
        board_.end_game(game_.good_code(), state);
        return;
    }

    game_.advance();
    board_.next_row();
}

} // namespace app
