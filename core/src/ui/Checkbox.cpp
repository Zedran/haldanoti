// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <cassert>
#include <utility>

#include <SFML/Window/Mouse.hpp>

#include "ui/Checkbox.hpp"
#include "ui/Layout.hpp"

namespace ui {

sf::String Checkbox::check_mark_{};

Checkbox::Checkbox(
    const sf::Font& font,
    sf::Vector2f    size,
    Checkbox::Style style,
    sf::String      label_text
) : Box{size, style.box, ui::Layout::Type::RowLayout},
    state_{},
    style_(style) {
    constexpr ui::Box::Style INNER_BOX_STYLE{.bg{0}, .ol{0}};

    ui::Box& lbox = add_component<ui::Box>(
        size.componentWiseMul(LABEL_REL_SIZE),
        INNER_BOX_STYLE,
        ui::Layout::Type::RowLayout
    );

    ui::Box& rbox = add_component<ui::Box>(
        size.componentWiseMul({1.0f - LABEL_REL_SIZE.x, LABEL_REL_SIZE.y}),
        INNER_BOX_STYLE,
        ui::Layout::Type::RowLayout
    );

    lbox.add_component<ui::Label>(
        font,
        size.componentWiseMul(LABEL_REL_SIZE),
        style.label,
        std::move(label_text)
    );

    cb_ = &rbox.add_component<ui::Button>(
        font,
        sf::Vector2f{size.y * CHECKBOX_REL_SIZE.x, size.y * CHECKBOX_REL_SIZE.y},
        style.button_off,
        sf::String{}
    );
    cb_->bind(sf::Mouse::Button::Left, [this] { flip_state(); });
}

Checkbox::~Checkbox() = default;

bool Checkbox::get_state() const noexcept {
    return state_;
}

void Checkbox::enable() {
    assert(cb_);

    state_ = true;
    cb_->set_text(check_mark_);
    cb_->set_style(style_.button_on);
}

void Checkbox::disable() {
    assert(cb_);

    state_ = false;
    cb_->set_text({});
    cb_->set_style(style_.button_off);
}

void Checkbox::flip_state() {
    if (state_) {
        disable();
    } else {
        enable();
    }
}

void Checkbox::set_check_mark(sf::String mark) noexcept {
    check_mark_ = std::move(mark);
}

void Checkbox::set_state(bool s) {
    if (s) {
        enable();
    } else {
        disable();
    }
}

} // namespace ui
