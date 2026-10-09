// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <filesystem>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "config/Config.hpp"
#include "os/os.hpp"
#include "utils/assets.hpp"

namespace config {

// Queries system locale for the language. If the language is supported
// by the application, its code is returned. Otherwise, the default code
// is used as a fallback.
static std::string get_default_lang_code() {
    const std::vector<sf::String> langs = utils::get_lang_fnames();

    std::string sys_lang = os::get_sys_lang_code().value_or(std::string{utils::DEFAULT_LANG_CODE});

    if (std::find(langs.begin(), langs.end(), sf::String{sys_lang}) != langs.end()) {
        return sys_lang;
    }
    return std::string{utils::DEFAULT_LANG_CODE};
}

void from_json(const nlohmann::json& j, Config& v) {
    // Lazily loaded default Config.
    std::unique_ptr<Config> default_config;

    const auto has = [&j, &default_config](const std::string& key) {
        if (j.contains(key)) {
            return true;
        }
        if (!default_config) {
            default_config = std::make_unique<Config>(get_default_config());
        }
        return false;
    };

    v.code_chars   = has("code_chars") ? j["code_chars"].get<bool>() : default_config->code_chars;
    v.fb_chars     = has("fb_chars") ? j["fb_chars"].get<bool>() : default_config->fb_chars;
    v.hints        = has("hints") ? j["hints"].get<bool>() : default_config->hints;
    v.lang         = has("lang") ? j["lang"].get<std::string>() : default_config->lang;
    v.theme        = has("theme") ? j["theme"].get<std::string>() : default_config->theme;
    v.unique_elems = has("unique_elems") ? j["unique_elems"].get<bool>() : default_config->unique_elems;
    v.vsync        = has("vsync") ? j["vsync"].get<bool>() : default_config->vsync;
}

Config get_default_config() {
    return Config{
        .code_chars   = true,
        .fb_chars     = false,
        .hints        = false,
        .lang         = get_default_lang_code(),
        .theme        = std::string{utils::DEFAULT_THEME},
        .unique_elems = true,
        .vsync        = false,
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

void to_json(nlohmann::json& j, const Config& v) {
    j["code_chars"]   = v.code_chars;
    j["fb_chars"]     = v.fb_chars;
    j["hints"]        = v.hints;
    j["lang"]         = v.lang;
    j["theme"]        = v.theme;
    j["unique_elems"] = v.unique_elems;
    j["vsync"]        = v.vsync;
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
