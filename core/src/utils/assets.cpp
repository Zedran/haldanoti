// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <cstdlib>
#include <filesystem>
#include <locale>

#include <nlohmann/json.hpp>

#include "lang/default_lang.hpp"
#include "utils/assets.hpp"

namespace utils {

std::filesystem::path find_config_dir() {
    char* home{};

#if defined(__linux__)
    bool xdg_var_set{true};

    home = std::getenv("XDG_CONFIG_HOME");
    if (!home) {
        home        = std::getenv("HOME");
        xdg_var_set = false;
    }
#elif defined(_WIN32)
    home = std::getenv("APPDATA");
#endif

    if (!home) {
        throw std::runtime_error{"could not resolve config path"};
    }

    std::filesystem::path config_dir{home};

#if defined(__linux__)
    if (!xdg_var_set) {
        config_dir /= ".config";
    }
#endif

    constexpr auto MM_DIR_NAME{"mm-game"};

    return config_dir / MM_DIR_NAME;
}

std::vector<sf::String> get_lang_fnames() {
    std::vector<sf::String> fnames;

    for (const auto& d : {LANG_DIR_PATH_SYS, LANG_DIR_PATH_DEV}) {
        const std::filesystem::path dir{d};

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

    // Add the default language.
    fnames.push_back("en");

    return fnames;
}

std::string get_system_language() {
    return std::locale{""}.name().substr(0, 2);
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

lang::Lang load_language(
    std::array<std::string, 2> lang_dirs,
    std::optional<std::string> lang_fname
) {
    std::string pref_lang = lang_fname ? lang_fname.value() : get_system_language();

    if (pref_lang == "en") {
        return lang::DEFAULT_LANG;
    }

    const auto ext = [&pref_lang](std::string fname) {
        fname += '/' + pref_lang;
        return fname.ends_with(".json") ? fname : fname + ".json";
    };

    std::ifstream lf;
    try {
        lf = load_asset<std::ifstream>({ext(lang_dirs[0]), ext(lang_dirs[1])});
    } catch (const std::runtime_error&) {
        return lang::DEFAULT_LANG;
    }

    nlohmann::json j = nlohmann::json::parse(lf);
    return j.get<lang::Lang>();
}

} // namespace utils
