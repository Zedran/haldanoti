// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <cstdlib>
#include <filesystem>
#if defined(_WIN32)
#include <climits>
#include <cstddef>
#include <cstdlib>
#include <windows.h>
#else
#include <locale>
#endif

#include <nlohmann/json.hpp>

#include "lang/default_lang.hpp"
#include "utils/assets.hpp"
#include "utils/debug.hpp"
#if defined(_WIN32)
#include "utils/FinalAction.hpp"
#endif

namespace utils {

std::filesystem::path find_app_data_dir() {
#if defined(_WIN32)
    // Reference: https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulefilenamew

    wchar_t buffer[MAX_PATH];

    const DWORD n = GetModuleFileNameW(nullptr, buffer, MAX_PATH);
    if (n == 0) {
        throw std::runtime_error{"unable to determine executable path"};
    }

    return std::filesystem::path{buffer}.parent_path().parent_path();
#else
    return std::filesystem::path{DEF_APP_DATA_DIR_SYS};
#endif
}

std::filesystem::path find_cache_dir() {
    char* home{};

#if defined(__linux__)
    bool xdg_var_set{true};

    home = std::getenv("XDG_CACHE_HOME");
    if (!home) {
        home        = std::getenv("HOME");
        xdg_var_set = false;
    }
#elif defined(_WIN32)
    const auto finally = utils::finally([home] { if (home) { free(home); } });

    std::size_t   size{};
    const errno_t err = _dupenv_s(&home, &size, "LOCALAPPDATA");

    if (err != 0 || size == 0) {
        throw std::runtime_error{"LOCALAPPDATA env var not found (" + std::to_string(err) + ')'};
    }
#endif

    if (!home) {
        throw std::runtime_error{"could not resolve cache path"};
    }

    std::filesystem::path cache_dir{home};

#if defined(__linux__)
    if (!xdg_var_set) {
        cache_dir /= ".cache";
    }
#endif

    constexpr auto MM_DIR_NAME{"mm-game"};

    return cache_dir / MM_DIR_NAME;
}

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
    const auto finally = utils::finally([home] { if (home) { free(home); } });

    std::size_t   size{};
    const errno_t err = _dupenv_s(&home, &size, "APPDATA");

    if (err != 0 || size == 0) {
        throw std::runtime_error{"APPDATA env var not found (" + std::to_string(err) + ')'};
    }
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

std::optional<std::string> get_sys_lang_code() {
#if defined(_WIN32)
    // Reference: https://learn.microsoft.com/en-us/windows/win32/api/winnls/nf-winnls-getuserdefaultlocalename

    wchar_t   buffer[LOCALE_NAME_MAX_LENGTH];
    const int n = GetUserDefaultLocaleName(buffer, std::size(buffer));
    // Assuming output structured as follows: "pl-PL ".

    if (n < 2) {
        dbg("locale lookup failed");
        return std::nullopt;
    }

    const auto is_ascii = [](wchar_t c) {
        return c >= CHAR_MIN && c <= CHAR_MAX;
    };

    if (!is_ascii(buffer[0]) || !is_ascii(buffer[1])) {
        dbg("buffer elements are non-ASCII characters");
        return std::nullopt;
    }

    return std::string(buffer, buffer + 2);
#else
    const std::string lang = std::locale{""}.name();

    if (lang.size() < 2) {
        dbg("locale lookup failed (got '{}')", lang);
        return std::nullopt;
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

lang::Lang load_language(std::string lang_fname) {
    if (lang_fname.empty()) {
        lang_fname = get_sys_lang_code().value_or(std::string{DEFAULT_LANG_CODE});
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
