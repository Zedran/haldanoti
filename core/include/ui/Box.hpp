// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <concepts>
#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#include "ui/Layout.hpp"
#include "ui/Widget.hpp"

namespace ui {

// Box is a container for other Widget types.
class Box : public Widget {
public:
    struct Style {
        sf::Color bg;
        sf::Color ol;
    };

    Box(sf::Vector2f size, Style style, Layout::Type layout);

    virtual ~Box();

    template <typename T, typename... Args>
        requires std::derived_from<T, Widget>
    T& add_component(Args&&... args) {
        auto& ref = components_.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
        return *static_cast<T*>(ref.get());
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    const Widget& get_component(std::size_t index) const;

    virtual sf::Vector2f get_position() const override;

    virtual sf::Vector2f get_size() const override;

    virtual void handle_event(const sf::Event& event) override;

    void layout_components();

    void pop_component() noexcept;

    virtual void set_position(sf::Vector2f pos) override;

    void set_style(Style style);

private:
    // This struct holds information on whether individual visual elements
    // are visible. Each time set_style is called, colors of the new Style
    // are evaluated in regards to their alpha value. The ones with alpha
    // value of 0 are not drawn. This evaluation reduces the amount of
    // unnecessary calls to RenderTarget::draw.
    struct Visible {
        bool bg;
    };

    // Outline size in pixels.
    static constexpr float OUTLINE_SIZE{1.0f};

    sf::RectangleShape bg_;

    std::vector<std::unique_ptr<Widget>> components_;

    std::unique_ptr<Layout> layout_;

    Visible visible_;
};

} // namespace ui
