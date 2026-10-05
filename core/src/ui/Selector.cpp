// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <utility>

#include "ui/Selector.hpp"

namespace ui {

Selector::Selector(
    const sf::Font&         font,
    sf::Vector2f            size,
    Style                   style,
    sf::String              label,
    std::vector<sf::String> entries,
    Layout::Type            layout
) : Box{size, style.box, layout}, entries_{std::move(entries)}, index_{} {
    constexpr Box::Style INNER_BOX_STYLE{.bg{0}, .ol{0}};

    const sf::Vector2f label_rel_size =
        layout == Layout::Type::RowLayout
            ? LABEL_REL_SIZE_ROW
            : LABEL_REL_SIZE_COL;

    Box& lbox = add_component<Box>(
        size.componentWiseMul(label_rel_size),
        INNER_BOX_STYLE,
        Layout::Type::RowLayout
    );

    const sf::Vector2f rbox_size = size.componentWiseMul(
        layout == Layout::Type::RowLayout
            ? sf::Vector2f{1.0f - label_rel_size.x, label_rel_size.y}
            : sf::Vector2f{label_rel_size.x, 1.0f - label_rel_size.y}
    );

    Box& rbox = add_component<Box>(
        rbox_size,
        INNER_BOX_STYLE,
        Layout::Type::RowLayout
    );

    lbox.add_component<Label>(
        font,
        size.componentWiseMul(label_rel_size),
        style.label,
        std::move(label)
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

    if (entries_.empty()) {
        throw std::runtime_error{"no entries set for the Selector"};
    }

    if (entries_.size() == 1) {
        fwd.disable();
        rev.disable();
    } else {
        std::sort(entries_.begin(), entries_.end());
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

sf::String Selector::get_value() const {
    assert(index_ < entries_.size());
    return entries_[index_];
}

void Selector::increment() {
    if (index_ >= entries_.size() - 1) {
        index_ = 0;
    } else {
        index_++;
    }
    sel_label_->set_text(entries_[index_]);
}

void Selector::set_index(std::size_t index) {
    assert(index < entries_.size());
    index_ = index;
    sel_label_->set_text(entries_[index]);
}

void Selector::set_value(const sf::String& v) {
    for (std::size_t i = 0; i < entries_.size(); i++) {
        if (entries_[i] == v) {
            set_index(i);
            return;
        }
    }
    throw std::logic_error{"value '" + v.toAnsiString() + "' not found in the Selector"};
}

} // namespace ui
