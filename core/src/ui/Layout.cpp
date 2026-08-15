// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <stdexcept>

#include <SFML/System/Vector2.hpp>

#include "ui/Layout.hpp"

namespace ui {

ColumnLayout::ColumnLayout() noexcept = default;

ColumnLayout::~ColumnLayout() = default;

void ColumnLayout::place(sf::FloatRect container, std::span<std::unique_ptr<Widget>> widgets) {
    if (widgets.empty()) {
        return;
    }

    float widget_space_y{0.0f};

    for (const auto& w : widgets) {
        widget_space_y += w->get_size().y;
    }

    const float pad_space_y{container.size.y - widget_space_y};
    const float pady_per_elem{pad_space_y / static_cast<float>(widgets.size() + 1)};

    sf::Vector2f pos = container.position;

    const float container_x = pos.x;

    for (std::size_t i = 0; i < widgets.size(); i++) {
        pos.x  = container_x + (container.size.x - widgets[i]->get_size().x) / 2.0f;
        pos.y += pady_per_elem;

        widgets[i]->set_position({pos.x, pos.y});

        pos.y += widgets[i]->get_size().y;
    }
}

RowLayout::RowLayout() noexcept = default;

RowLayout::~RowLayout() = default;

void RowLayout::place(sf::FloatRect container, std::span<std::unique_ptr<Widget>> widgets) {
    if (widgets.empty()) {
        return;
    }

    float widget_space_x{0.0f};

    for (const auto& w : widgets) {
        widget_space_x += w->get_size().x;
    }

    const float pad_space_x{container.size.x - widget_space_x};
    const float padx_per_elem{pad_space_x / static_cast<float>(widgets.size() + 1)};

    sf::Vector2f pos = container.position;

    const float container_y = pos.y;

    for (std::size_t i = 0; i < widgets.size(); i++) {
        pos.x += padx_per_elem;
        pos.y  = container_y + (container.size.y - widgets[i]->get_size().y) / 2.0f;

        widgets[i]->set_position({pos.x, pos.y});

        pos.x += widgets[i]->get_size().x;
    }
}

std::unique_ptr<Layout> make_layout(Layout::Type layout_type) {
    switch (layout_type) {
    case Layout::Type::ColumnLayout: return std::make_unique<ColumnLayout>();
    case Layout::Type::RowLayout:    return std::make_unique<RowLayout>();
    }
    throw std::invalid_argument{"unknown layout type"};
}

} // namespace ui
