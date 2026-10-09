// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <string>

#include "utils/json.hpp"
#include "utils/utils.hpp"

namespace sf {

void from_json(const nlohmann::json& j, sf::Color& v) {
    v = utils::decode_color(j.get<std::string>());
}

void from_json(const nlohmann::json& j, sf::String& v) {
    std::string utf8 = j.get<std::string>();
    v                = sf::String::fromUtf8(utf8.begin(), utf8.end());
}

} // namespace sf
