// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <string>

#include <nlohmann/json.hpp>

namespace config {

struct Config {
    // Always display feedback characters, regardless of the theme's settings.
    bool fb_chars;

    // Display hints regarding secret code elements.
    bool hints;

    // Language used by the application.
    std::string lang;

    // Does not permit repeating elements in the generated code.
    bool unique_elems;

    // Run the game at a native framerate.
    bool vsync;

    bool operator==(const Config& other) const noexcept = default;
};

// Deserializes Config from JSON. Fills missing values with defaults.
void from_json(const nlohmann::json& j, Config& v);

Config get_default_config();

// Returns Config read from the config directory.
Config read_config();

// Serializes Config into JSON.
void to_json(nlohmann::json& j, const Config& v);

// Writes Config to file at path.
void write_config(const Config& conf);

} // namespace config
