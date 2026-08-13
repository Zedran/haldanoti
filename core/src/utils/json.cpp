// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include "utils/json.hpp"

namespace std {

void from_json(const nlohmann::json& j, std::optional<std::string>& v) {
    if (auto s = j.get<std::string>(); !s.empty()) {
        v = std::move(s);
    }
}

void to_json(nlohmann::json& j, const std::optional<std::string> v) {
    j = v ? *v : "";
}

} // namespace std

namespace sf {

void from_json(const nlohmann::json& j, sf::String& v) {
    std::string utf8 = j.get<std::string>();
    v                = sf::String::fromUtf8(utf8.begin(), utf8.end());
}

} // namespace sf
