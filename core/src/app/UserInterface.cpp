// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <utility>

#include "app/UserInterface.hpp"
#include "utils/assets.hpp"
#include "utils/debug.hpp"

namespace app {

UserInterface::UserInterface(
    sf::Vector2f   window_size,
    config::Config conf,
    lang::Lang     lang,
    theme::Theme   theme,
    sf::String     version
) : font_{utils::load_asset<sf::Font>("InterVariable.ttf")},
    bg_{theme.bg},
    board_{
        font_,
        window_size.componentWiseMul(Board::REL_SIZE),
        std::move(lang.board),
        std::move(theme.board)
    },
    message_{
        font_,
        window_size.componentWiseMul(Message::REL_SIZE),
        std::move(lang.message),
        theme.message
    },
    scene_{Scene::Game},
    settings_{
        font_,
        window_size,
        std::move(lang.settings),
        theme.settings,
        utils::get_lang_fnames(),
        std::move(version)
    },
    signal_{Signal::None},
    toolbar_{
        font_,
        window_size.componentWiseMul(Toolbar::REL_SIZE),
        std::move(lang.toolbar),
        theme.toolbar,
        [this] { this->set_signal(Signal::NewGame); },
        [this] { this->set_scene(Scene::Settings); },
        [this] { this->set_signal(Signal::Exit); }
    } {
    board_.set_position({
        (1 - Board::REL_SIZE.x) / 2 * window_size.x,
        (1 - Board::REL_SIZE.y - Toolbar::REL_SIZE.y) / 2 * window_size.y,
    });

    toolbar_.set_position({
        0.0f,
        (1.0f - Toolbar::REL_SIZE.y) * window_size.y,
    });

    message_.set_position({
        0.0f,
        0.8f * window_size.y,
    });

    settings_.set_position({
        0.0f,
        0.0f,
    });

    settings_.set_config(conf);
}

UserInterface::~UserInterface() = default;

void UserInterface::draw(Window& window) {
    window.clear(bg_);

    window.draw(board_);
    window.draw(toolbar_);

    if (scene_ == Scene::Settings) {
        window.draw(settings_);
    }

    window.draw(message_);

    window.display();
}

UserInterface::Signal UserInterface::emit_signal() noexcept {
    Signal current = signal_;
    signal_        = Signal::None;
    return current;
}

Board& UserInterface::get_board() noexcept {
    return board_;
}

Settings& UserInterface::get_settings() noexcept {
    return settings_;
}

void UserInterface::handle_event(const sf::Event& event) {
    switch (scene_) {
    case Scene::Game:
        board_.handle_event(event);
        toolbar_.handle_event(event);
        break;
    case Scene::Settings:
        settings_.handle_event(event);
    }
}

void UserInterface::reset() {
    board_.reset();
    signal_ = Signal::None;
}

void UserInterface::set_hints(std::optional<std::size_t> hint) {
    board_.set_hints(hint);
}

void UserInterface::set_scene(Scene scene) noexcept {
    dbg("setting scene {}", static_cast<int>(scene));

    scene_ = scene;

    if (scene == Scene::Settings) {
        settings_.set_state(Settings::State::Running);
    }
}

void UserInterface::set_signal(Signal signal) noexcept {
    signal_ = signal;
}

void UserInterface::show_message(Message::Content msg) {
    message_.show(msg);
}

void UserInterface::update() {
    message_.tick();

    if (scene_ == Scene::Settings) {
        switch (settings_.get_state()) {
        case Settings::State::Running:
            break;
        case Settings::State::SaveAndClose:
            signal_ = Signal::SaveConfig;
            set_scene(Scene::Game);
            break;
        case Settings::State::Close:
            set_scene(Scene::Game);
            break;
        }
    }
}

} // namespace app
