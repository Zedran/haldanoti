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

Config get_default_config() {
    const std::vector<sf::String> langs = utils::get_lang_fnames();

    std::string sys_lang = utils::get_system_language();

    Config c;

    if (std::find(langs.begin(), langs.end(), sf::String{sys_lang}) != langs.end()) {
        c.pref_language = std::move(sys_lang);
    } else {
        c.pref_language = "en";
    }

    c.unique_elems = true;

    return c;
}

config::Config read_config() {
    std::ifstream conf_file{utils::CONFIG_PATH};
    if (!conf_file.good()) {
        Config c = get_default_config();
        write_config(c);
        return c;
    }

    nlohmann::json j = nlohmann::json::parse(conf_file);
    return j.get<config::Config>();
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
