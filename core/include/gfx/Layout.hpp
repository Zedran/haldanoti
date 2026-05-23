#pragma once

#include <memory>
#include <span>

#include <SFML/Graphics/Rect.hpp>

#include "gfx/Widget.hpp"

namespace gfx::ui {

// Abstract base class for every Layout type.
struct Layout {
    enum class Type {
        ColumnLayout,
        RowLayout,
    };

    virtual ~Layout() = default;

    // Main function of the Layout. Accepts position and size of the outer
    // container and uses this information to position widgets wthin the
    // specified bounds.
    virtual void place(sf::FloatRect container, std::span<std::unique_ptr<Widget>> widgets) = 0;
};

// Places elements spaced evenly across a single column.
struct ColumnLayout : public Layout {
    ColumnLayout() noexcept;

    virtual ~ColumnLayout();

    void place(sf::FloatRect container, std::span<std::unique_ptr<Widget>> widgets) override final;
};

// Places elements spaced evenly across a single row.
struct RowLayout : public Layout {
    RowLayout() noexcept;

    virtual ~RowLayout();

    void place(sf::FloatRect container, std::span<std::unique_ptr<Widget>> widgets) override final;
};

std::unique_ptr<Layout> make_layout(Layout::Type layout_type);

} // namespace gfx::ui
