// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <optional>
#include <string>

#include <nlohmann/json.hpp>

#include "utils/json.hpp" // IWYU pragma: keep

namespace config {

struct Config {
    // Preferred language, chosen if found. Setting this field disregards
    // system's locale settings.
    std::optional<std::string> pref_language;

    // Does not permit repeating elements in the generated code.
    bool unique_elems;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Config, pref_language, unique_elems);

} // namespace config
