// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include "ui/Selector.hpp"

namespace ui {

Selector::Selector(
    const sf::Font&         font,
    sf::Vector2f            size,
    Style                   style,
    sf::String              label_text,
    std::vector<sf::String> entries
) : Box{size, style.box, Layout::Type::RowLayout}, entries_{entries}, index_{} {
    constexpr Box::Style INNER_BOX_STYLE{.bg{0}, .ol{0}};

    Box& lbox = add_component<Box>(
        size.componentWiseMul(LABEL_REL_SIZE),
        INNER_BOX_STYLE,
        Layout::Type::RowLayout
    );

    const sf::Vector2f rbox_size = size.componentWiseMul({1.0f - LABEL_REL_SIZE.x, LABEL_REL_SIZE.y});

    Box& rbox = add_component<Box>(
        rbox_size,
        INNER_BOX_STYLE,
        Layout::Type::RowLayout
    );

    lbox.add_component<Label>(
        font,
        size.componentWiseMul(LABEL_REL_SIZE),
        style.label,
        label_text
    );

    const sf::Vector2f sel_button_size{rbox_size.y, rbox_size.y};

    Button& rev = rbox.add_component<Button>(
        font,
        sel_button_size,
        style.button,
        L"<"
    );
    rev.bind(sf::Mouse::Button::Left, [this] { this->decrement(); });

    sel_label_ = &rbox.add_component<Label>(
        font,
        rbox_size.componentWiseMul(LABEL_TO_RBOX_REL_SIZE),
        style.label,
        L""
    );

    Button& fwd = rbox.add_component<Button>(
        font,
        sel_button_size,
        style.button,
        L">"
    );
    fwd.bind(sf::Mouse::Button::Left, [this] { this->increment(); });

    if (entries_.size() < 2) {
        fwd.disable();
        rev.disable();
    }
}

Selector::~Selector() = default;

void Selector::decrement() {
    if (index_ == 0) {
        index_ = entries_.size() - 1;
    } else {
        index_--;
    }
    sel_label_->set_text(entries_[index_]);
}

std::size_t Selector::get_value() const noexcept {
    return index_;
}

void Selector::increment() {
    if (index_ >= entries_.size() - 1) {
        index_ = 0;
    } else {
        index_++;
    }
    sel_label_->set_text(entries_[index_]);
}

void Selector::set_value(std::size_t index) {
    index_ = index;
    sel_label_->set_text(entries_.at(index));
}

} // namespace ui
