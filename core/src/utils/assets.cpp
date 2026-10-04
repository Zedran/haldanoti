// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <nlohmann/json.hpp>

#include "utils/assets.hpp"

namespace utils {

std::vector<sf::String> get_lang_fnames() {
    std::vector<sf::String> fnames;

    const std::filesystem::path dir = APP_DATA_DIR / ASSETS_DIRNAME / LANG_DIRNAME;

    if (std::filesystem::exists(dir)) {
        for (const auto& p : list_files(dir)) {
            fnames.push_back(p.filename().replace_extension({}).string());
        }
    }

    if (fnames.empty()) {
        throw std::runtime_error{"could not find language files"};
    }

    return fnames;
}

std::vector<sf::String> get_theme_fnames() {
    std::vector<sf::String> fnames;

    const std::filesystem::path dir = APP_DATA_DIR / ASSETS_DIRNAME / THEME_DIRNAME;

    if (std::filesystem::exists(dir)) {
        for (const auto& p : list_files(dir)) {
            fnames.push_back(p.filename().replace_extension({}).string());
        }
    }

    if (fnames.empty()) {
        throw std::runtime_error{"could not find theme files"};
    }

    return fnames;
}

std::vector<std::filesystem::path> list_files(const std::filesystem::path& dir) {
    std::vector<std::filesystem::path> files;

    for (const auto& e : std::filesystem::directory_iterator{dir}) {
        if (e.is_regular_file()) {
            files.push_back(e);
        }
    }

    return files;
}

lang::Lang load_language(std::string lang_fname) {
    if (lang_fname.empty()) {
        lang_fname = os::get_sys_lang_code().value_or(std::string{DEFAULT_LANG_CODE});
    }

    if (!lang_fname.ends_with(".json")) {
        lang_fname += ".json";
    }

    std::ifstream lf;
    try {
        lf = load_asset<std::ifstream>(LANG_DIRNAME / lang_fname);
    } catch (const std::runtime_error&) {
        if (lang_fname.starts_with(DEFAULT_LANG_CODE)) {
            throw;
        }
        lf = load_asset<std::ifstream>((LANG_DIRNAME / DEFAULT_LANG_CODE).replace_extension(".json"));
    }

    nlohmann::json j = nlohmann::json::parse(lf);
    return j.get<lang::Lang>();
}

theme::Theme load_theme(std::string theme_fname) {
    if (theme_fname.empty()) {
        theme_fname = os::get_sys_lang_code().value_or(std::string{DEFAULT_THEME});
    }

    if (!theme_fname.ends_with(".json")) {
        theme_fname += ".json";
    }

    std::ifstream lf;
    try {
        lf = load_asset<std::ifstream>(THEME_DIRNAME / theme_fname);
    } catch (const std::runtime_error&) {
        if (theme_fname.starts_with(DEFAULT_THEME)) {
            throw;
        }
        lf = load_asset<std::ifstream>((THEME_DIRNAME / DEFAULT_THEME).replace_extension(".json"));
    }

    nlohmann::json j = nlohmann::json::parse(lf);
    return j.get<theme::Theme>();
}

} // namespace utils
