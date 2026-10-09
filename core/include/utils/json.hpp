// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/String.hpp>
#include <nlohmann/json.hpp>

#include "ui/Box.hpp"
#include "ui/Button.hpp"
#include "ui/Checkbox.hpp"
#include "ui/Label.hpp"
#include "ui/Selector.hpp"

namespace sf {

// Converts JSON string to SFML Color.
void from_json(const nlohmann::json& j, sf::Color& v);

// Converts JSON string to SFML String.
void from_json(const nlohmann::json& j, sf::String& v);

} // namespace sf

namespace ui {

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Label::Style, bg, fg, ol);

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Box::Style, bg, ol);

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Button::Style, disabled, normal, active, hover);

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Checkbox::Style, box, button_off, button_on, label);

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Selector::Style, box, label, button);

} // namespace ui
