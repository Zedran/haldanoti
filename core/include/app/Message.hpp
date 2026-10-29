// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <cstdint>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

#include "lang/Message.hpp"
#include "ui/Label.hpp"

namespace app {

// Specialized Label that is only displayed for a short time to convey
// a message to the player.
class Message final : public ui::Label {
public:
    enum class Content {
        RestartRequired,
        StartingNewGame,
    };

    // Label size relative to the game window.
    static constexpr sf::Vector2f REL_SIZE{1.0f, 0.08f};

    Message(
        const sf::Font&  font,
        sf::Vector2f     size,
        lang::Message    lang,
        ui::Label::Style style
    );

    ~Message();

    // Draws the Label if it is active (its clock is running).
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

    // Sets the content of the Message and shows it.
    void show(Content msg);

    // Measures elapsed time and disables the Message after the intended
    // time has passed.
    void tick();

private:
    // Display time in milliseconds.
    static constexpr std::int32_t DISPLAY_TIME = 3000;

    // Font size relative to the size.y of the Message's Label.
    static constexpr float FONT_REL_SIZE{0.35f};

    sf::Clock clock_;

    lang::Message lang_;
};

} // namespace app
