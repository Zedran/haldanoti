// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <cstdlib>
#include <filesystem>
#if defined(WIN32)
#include <climits>
#include <windows.h>
#include <winnls.h>
#else
#include <locale>
#endif

#include <nlohmann/json.hpp>

#include "lang/default_lang.hpp"
#include "utils/assets.hpp"
#include "utils/debug.hpp"

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

    fnames.push_back(sf::String{DEFAULT_LANG_CODE});

    return fnames;
}

std::string get_sys_lang_code() {
#if defined(WIN32)
    // Reference: https://learn.microsoft.com/en-us/windows/win32/api/winnls/nf-winnls-getuserdefaultlocalename

    wchar_t   buffer[LOCALE_NAME_MAX_LENGTH];
    const int n = GetUserDefaultLocaleName(buffer, std::size(buffer));
    // Assuming output structured as follows: "pl-PL ".

    if (n < 2) {
        dbg("locale lookup failed, fallback to '{}'", DEFAULT_LANG_CODE);
        return std::string{DEFAULT_LANG_CODE};
    }

    const auto is_ascii = [](wchar_t c) {
        return c >= CHAR_MIN && c <= CHAR_MAX;
    };

    if (!is_ascii(buffer[0]) || !is_ascii(buffer[1])) {
        dbg("buffer elements are non-ASCII characters, fallback to '{}'", DEFAULT_LANG_CODE);
        return std::string{DEFAULT_LANG_CODE};
    }

    return std::string(buffer, buffer + 2);
#else
    const std::string lang = std::locale{""}.name();

    if (lang.size() < 2) {
        dbg("locale lookup failed (got '{}'), fallback to '{}'", lang, DEFAULT_LANG_CODE);
        return std::string{DEFAULT_LANG_CODE};
    }

    return lang.substr(0, 2);
#endif
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
    std::string                lang_fname
) {
    if (lang_fname.empty()) {
        lang_fname = get_sys_lang_code();
    }

    if (lang_fname == DEFAULT_LANG_CODE) {
        return lang::DEFAULT_LANG;
    }

    const auto ext = [&lang_fname](std::string fname) {
        fname += '/' + lang_fname;
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
