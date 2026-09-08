// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <SFML/System/Time.hpp>

#include "app/Message.hpp"

namespace app {

Message::Message(
    const sf::Font&  font,
    sf::Vector2f     size,
    lang::Message    lang,
    ui::Label::Style style
) : ui::Label{font, size, style, {}, static_cast<unsigned int>(size.y * FONT_REL_SIZE)},
    lang_{lang} {
    clock_.reset();
}

Message::~Message() = default;

void Message::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (clock_.isRunning()) {
        ui::Label::draw(target, states);
    }
}

void Message::show(Content msg) {
    switch (msg) {
    case Content::RestartRequired: set_text(lang_.restart_required); break;
    };
    clock_.start();
}

void Message::tick() {
    if (!clock_.isRunning()) {
        return;
    }

    const std::int32_t elapsed = clock_.getElapsedTime().asMilliseconds();
    if (elapsed > DISPLAY_TIME) {
        clock_.reset();
    }
}

} // namespace app
