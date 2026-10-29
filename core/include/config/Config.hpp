// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <cstddef>
#include <string>

#include <nlohmann/json.hpp>

namespace config {

// Maximum code length.
constexpr std::size_t CODE_LEN_MAX = 6;

// Minimum code length.
constexpr std::size_t CODE_LEN_MIN = 3;

struct Config {
    // Display code characters.
    bool code_chars;

    // Number of elements in the code.
    std::size_t code_len;

    // Display feedback characters.
    bool fb_chars;

    // Display hints regarding secret code elements.
    bool hints;

    // Language used by the application.
    std::string lang;

    // Name of the selected color theme.
    std::string theme;

    // Does not permit repeating elements in the generated code.
    bool unique_elems;

    // Run the game at a native framerate.
    bool vsync;

    bool operator==(const Config& other) const noexcept = default;
};

// Ensures that all values in c are within assumed limits.
void enforce_limits(Config& c) noexcept;

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
