// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <SFML/System/String.hpp>
#include <nlohmann/json.hpp>

#include "utils/json.hpp" // IWYU pragma: keep

namespace lang {

struct FeedbackLabel {
    sf::String red;
    sf::String white;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(FeedbackLabel, red, white);

} // namespace lang
