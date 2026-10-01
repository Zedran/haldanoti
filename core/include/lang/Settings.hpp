// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <SFML/System/String.hpp>
#include <nlohmann/json.hpp>

#include "utils/json.hpp" // IWYU pragma: keep

namespace lang {

struct Settings {
    sf::String check_mark;
    sf::String title;
    sf::String opt_unique_elems;
    sf::String opt_lang;
    sf::String opt_code_chars;
    sf::String opt_fb_chars;
    sf::String opt_hints;
    sf::String opt_vsync;
    sf::String save;
    sf::String cancel;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(
    Settings,
    check_mark,
    title,
    opt_unique_elems,
    opt_lang,
    opt_code_chars,
    opt_fb_chars,
    opt_hints,
    opt_vsync,
    save,
    cancel
);

} // namespace lang
