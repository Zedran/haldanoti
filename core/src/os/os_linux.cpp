// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#if defined(__linux__)

#include <cstdlib>
#include <stdexcept>

#include "os/os.hpp"

namespace os {

std::filesystem::path find_app_data_dir() {
    return std::filesystem::path{DEF_APP_DATA_DIR_SYS};
}

std::filesystem::path find_cache_dir() {
    char* home{};

    bool xdg_var_set{true};

    home = std::getenv("XDG_CACHE_HOME");
    if (!home) {
        home        = std::getenv("HOME");
        xdg_var_set = false;
    }

    if (!home) {
        throw std::runtime_error{"could not resolve cache path"};
    }

    std::filesystem::path cache_dir{home};

    if (!xdg_var_set) {
        cache_dir /= ".cache";
    }

    return cache_dir;
}

std::filesystem::path find_config_dir() {
    char* home{};

    bool xdg_var_set{true};

    home = std::getenv("XDG_CONFIG_HOME");
    if (!home) {
        home        = std::getenv("HOME");
        xdg_var_set = false;
    }

    if (!home) {
        throw std::runtime_error{"could not resolve config path"};
    }

    std::filesystem::path config_dir{home};

    if (!xdg_var_set) {
        config_dir /= ".config";
    }

    return config_dir;
}

} // namespace os

#endif
