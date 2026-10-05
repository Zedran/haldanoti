// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <algorithm>
#include <utility>

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

    for (const auto& dir : {THEME_DIR_USR, THEME_DIR_SYS}) {
        if (std::filesystem::exists(dir)) {
            for (const auto& p : list_files(dir)) {
                sf::String name = p.filename().replace_extension({}).string();

                if (std::find(fnames.begin(), fnames.end(), sf::String{p.filename()}) == fnames.end()) {
                    fnames.push_back(std::move(name));
                }
            }
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
        theme_fname = DEFAULT_THEME;
    }

    if (!theme_fname.ends_with(".json")) {
        theme_fname += ".json";
    }

    const auto parse_tf = [](const std::filesystem::path& p) {
        std::ifstream  tf = load_asset<std::ifstream>(p);
        nlohmann::json j  = nlohmann::json::parse(tf);
        return j.get<theme::Theme>();
    };

    if (theme_fname.starts_with(DEFAULT_THEME)) {
        return parse_tf((THEME_DIR_SYS / DEFAULT_THEME).replace_extension({".json"}));
    }

    for (const auto& dir : {THEME_DIR_USR, THEME_DIR_SYS}) {
        try {
            return parse_tf(dir / theme_fname);
        } catch (const std::runtime_error&) {
            // Ignore path errors and JSON parsing errors for custom themes.
            continue;
        }
    }

    // If custom theme parsing failed, fall back to the default theme.
    return parse_tf(THEME_DIR_SYS / DEFAULT_THEME);
}

} // namespace utils
