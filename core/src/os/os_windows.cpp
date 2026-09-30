// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#if defined(_WIN32)

#include <cstddef>
#include <cstdlib>
#include <stdexcept>
#include <windows.h>

#include "os/os.hpp"
#include "utils/FinalAction.hpp"
#include "utils/debug.hpp"

namespace os {

std::filesystem::path find_app_data_dir() {
    // Reference: https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulefilenamew

    wchar_t buffer[MAX_PATH];

    const DWORD n = GetModuleFileNameW(nullptr, buffer, MAX_PATH);
    if (n == 0) {
        throw std::runtime_error{"unable to determine executable path"};
    }

    std::filesystem::path path{buffer};
    path = path.parent_path().parent_path();

    dbg("{}", path.string());
    return path;
}

std::filesystem::path find_cache_dir() {
    char* env_var{};

    const auto finally = utils::finally([env_var] { if (env_var) { free(env_var); } });

    std::size_t   size{};
    const errno_t err = _dupenv_s(&env_var, &size, "LOCALAPPDATA");

    if (err != 0 || size == 0) {
        throw std::runtime_error{"LOCALAPPDATA env var not found (" + std::to_string(err) + ')'};
    }

    if (!env_var) {
        throw std::runtime_error{"could not resolve cache path"};
    }

    std::filesystem::path cache_dir{env_var};

    dbg("{}", cache_dir.string());
    return cache_dir;
}

std::filesystem::path find_config_dir() {
    char* env_var{};

    const auto finally = utils::finally([env_var] { if (env_var) { free(env_var); } });

    std::size_t   size{};
    const errno_t err = _dupenv_s(&env_var, &size, "APPDATA");

    if (err != 0 || size == 0) {
        throw std::runtime_error{"APPDATA env var not found (" + std::to_string(err) + ')'};
    }

    if (!env_var) {
        throw std::runtime_error{"could not resolve config path"};
    }

    std::filesystem::path config_dir{env_var};

    dbg("{}", config_dir.string());
    return config_dir;
}

std::optional<std::string> get_sys_lang_code() {
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

    std::string code = std::string(buffer, buffer + 2);

    dbg("{}", code);
    return code;
}

} // namespace os

#endif
