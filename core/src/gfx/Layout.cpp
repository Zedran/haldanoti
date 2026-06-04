#include <stdexcept>

#include <SFML/System/Vector2.hpp>

#include "gfx/Layout.hpp"

namespace ui {

ColumnLayout::ColumnLayout() noexcept = default;

ColumnLayout::~ColumnLayout() = default;

void ColumnLayout::place(sf::FloatRect container, std::span<std::unique_ptr<Widget>> widgets) {
    if (widgets.empty()) {
        return;
    }

    const float padx{(container.size.x - widgets[0]->get_size().x) / 2.0f};

    float widget_space_y{0.0f};

    for (const auto& w : widgets) {
        widget_space_y += w->get_size().y;
    }

    const float pad_space_y{container.size.y - widget_space_y};
    const float pady_per_elem{pad_space_y / static_cast<float>(widgets.size() + 1)};

    sf::Vector2f pos = container.position;

    pos.y += pady_per_elem;
    pos.x  = pos.x + padx;

    for (auto& w : widgets) {
        w->set_position(pos);
        pos.y += pady_per_elem + w->get_size().y;
        pos.y  = pos.y;
    }
}

RowLayout::RowLayout() noexcept = default;

RowLayout::~RowLayout() = default;

void RowLayout::place(sf::FloatRect container, std::span<std::unique_ptr<Widget>> widgets) {
    if (widgets.empty()) {
        return;
    }

    const float pady{(container.size.y - widgets[0]->get_size().y) / 2.0f};

    float widget_space_x{0.0f};

    for (const auto& w : widgets) {
        widget_space_x += w->get_size().x;
    }

    const float pad_space_x{container.size.x - widget_space_x};
    const float padx_per_elem{pad_space_x / static_cast<float>(widgets.size() + 1)};

    sf::Vector2f pos = container.position;

    pos.x += padx_per_elem;
    pos.y  = pos.y + pady;

    for (auto& w : widgets) {
        w->set_position(pos);
        pos.x += padx_per_elem + w->get_size().x;
        pos.x  = pos.x;
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
