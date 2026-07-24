// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <memory>
#include <span>

#include <SFML/Graphics/Rect.hpp>

#include "ui/Widget.hpp"

namespace ui {

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

    virtual void place(sf::FloatRect container, std::span<std::unique_ptr<Widget>> widgets) override;
};

// Places elements spaced evenly across a single row.
struct RowLayout : public Layout {
    RowLayout() noexcept;

    virtual ~RowLayout();

    virtual void place(sf::FloatRect container, std::span<std::unique_ptr<Widget>> widgets) override;
};

std::unique_ptr<Layout> make_layout(Layout::Type layout_type);

} // namespace ui
