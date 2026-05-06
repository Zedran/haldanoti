#include <SFML/System/Vector2.hpp>

#include "gfx/Layout.hpp"

namespace gfx::ui {

RowLayout::RowLayout() noexcept = default;

RowLayout::~RowLayout() = default;

void RowLayout::place(sf::FloatRect container, std::span<std::unique_ptr<Widget>> widgets) {
    const float pady{(container.size.y - widgets[0]->get_size().y) / 2.0f};

    float widget_space_x{0.0f};

    for (const auto& w : widgets) {
        widget_space_x += w->get_size().x;
    }

    const float pad_space_x{container.size.x - widget_space_x};
    const float padx_per_elem{pad_space_x / static_cast<float>(widgets.size() + 1)};

    sf::Vector2f pos = container.position;

    pos.x += padx_per_elem;
    pos.y  = std::round(pos.y + pady);

    for (auto& w : widgets) {
        w->set_position(pos);
        pos.x += padx_per_elem + w->get_size().x;
        pos.x  = std::round(pos.x);
    }
}

} // namespace gfx::ui
