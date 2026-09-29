// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <filesystem>

#include <nlohmann/json.hpp>

#include "lang/default_lang.hpp"
#include "utils/assets.hpp"

namespace utils {

std::vector<sf::String> get_lang_fnames() {
    std::vector<sf::String> fnames;

    const std::filesystem::path rel_path = ASSETS_DIRNAME / LANG_DIRNAME;

    for (const auto& d : {APP_DATA_SYS_PATH, std::filesystem::path{DEF_APP_DATA_DIR_DEV}}) {
        const std::filesystem::path dir = d / rel_path;

        if (std::filesystem::exists(dir)) {
            for (const auto& p : list_files(dir)) {
                fnames.push_back(p.filename().replace_extension({}).string());
            }
            if (!fnames.empty()) {
                // Only one, non-empty directory should be walked through.
                break;
            }
        }
    }

    if (fnames.empty()) {
        throw std::runtime_error{"could not find language files"};
    }

    fnames.push_back(sf::String{DEFAULT_LANG_CODE});

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

    if (lang_fname == DEFAULT_LANG_CODE) {
        return lang::DEFAULT_LANG;
    }

    if (!lang_fname.ends_with(".json")) {
        lang_fname += ".json";
    }

    std::ifstream lf;
    try {
        lf = load_asset<std::ifstream>(LANG_DIRNAME / lang_fname);
    } catch (const std::runtime_error&) {
        return lang::DEFAULT_LANG;
    }

    nlohmann::json j = nlohmann::json::parse(lf);
    return j.get<lang::Lang>();
}

} // namespace utils
