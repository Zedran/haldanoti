// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <SFML/System/String.hpp>
#include <nlohmann/json.hpp>

#include "lang/FeedbackLabel.hpp"
#include "lang/conversions.hpp" // IWYU pragma: keep

namespace lang {

struct GameRow {
    FeedbackLabel fb_label;
    sf::String    ok;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GameRow, fb_label, ok);

} // namespace lang
