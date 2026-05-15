#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#include "gfx/Layout.hpp"
#include "gfx/Widget.hpp"

namespace gfx::ui {

// Box is a container for other Widget types.
class Box : public Widget {
public:
    Box(sf::Vector2f size, sf::Color bg_color, Layout::Type layout);

    virtual ~Box();

    template <typename T, typename... Args>
    T& add_component(Args&&... args) {
        auto& ref = components_.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
        return *static_cast<T*>(ref.get());
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    virtual sf::Vector2f get_position() const override;

    virtual sf::Vector2f get_size() const override;

    virtual void handle_event(const sf::Event& event) override;

    virtual void set_position(sf::Vector2f pos) override;

private:
    sf::RectangleShape bg_;

    std::vector<std::unique_ptr<Widget>> components_;

    std::unique_ptr<Layout> layout_;
};

} // namespace gfx::ui
