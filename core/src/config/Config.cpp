// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "config/Config.hpp"
#include "utils/assets.hpp"

namespace config {

// Queries system locale for the language. If the language is supported
// by the application, its code is returned. Otherwise, the default code
// is used as a fallback.
static std::string get_default_lang_code() {
    const std::vector<sf::String> langs = utils::get_lang_fnames();

    std::string sys_lang = utils::get_sys_lang_code();

    if (std::find(langs.begin(), langs.end(), sf::String{sys_lang}) != langs.end()) {
        return sys_lang;
    }
    return utils::DEFAULT_LANG_CODE;
}

Config get_default_config() {
    return Config{
        .lang         = get_default_lang_code(),
        .unique_elems = true,
        .fb_chars     = false,
    };
}

config::Config read_config() {
    std::ifstream conf_file{utils::CONFIG_PATH};
    if (!conf_file.good()) {
        Config c = get_default_config();
        write_config(c);
        return c;
    }

    nlohmann::json j = nlohmann::json::parse(conf_file);

    Config c = j.get<config::Config>();

    if (c.lang.empty()) {
        c.lang = get_default_lang_code();
    }

    return c;
}

void write_config(const Config& conf) {
    if (!std::filesystem::exists(utils::CONFIG_DIR)) {
        std::filesystem::create_directories(utils::CONFIG_DIR);
    }

    std::ofstream conf_file{utils::CONFIG_PATH, std::ios::trunc};
    if (!conf_file.good()) {
        throw std::runtime_error{"failed to open config file"};
    }

    constexpr int JSON_INDENT = 4;

    const nlohmann::json j = conf;
    conf_file << j.dump(JSON_INDENT);
}

} // namespace config
