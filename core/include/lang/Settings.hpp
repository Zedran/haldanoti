// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <SFML/System/String.hpp>
#include <nlohmann/json.hpp>

#include "utils/json.hpp" // IWYU pragma: keep

namespace lang {

struct Settings {
    sf::String check_mark;
    sf::String label_unique_elems;
    sf::String label_language;
    sf::String save;
    sf::String cancel;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    Settings,
    check_mark,
    label_unique_elems,
    label_language,
    save,
    cancel
);

} // namespace lang
