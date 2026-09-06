// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <string>

#include <nlohmann/json.hpp>

namespace config {

struct Config {
    // Language used by the application.
    std::string lang;

    // Does not permit repeating elements in the generated code.
    bool unique_elems;

    // Always display feedback characters, regardless of the theme's settings.
    bool fb_chars;

    bool operator==(const Config& other) const noexcept = default;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Config, lang, unique_elems, fb_chars);

Config get_default_config();

// Returns Config read from the config directory.
Config read_config();

// Writes Config to file at path.
void write_config(const Config& conf);

} // namespace config
