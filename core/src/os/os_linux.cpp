// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#if defined(__linux__)

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <linux/limits.h>
#include <locale>
#include <stdexcept>
#include <sys/types.h>
#include <unistd.h>

#include "os/os.hpp"
#include "utils/debug.hpp"

namespace os {

std::filesystem::path find_app_data_dir() {
    char buffer[PATH_MAX + 1];

    const ssize_t n = readlink("/proc/self/exe", buffer, PATH_MAX);
    if (n == -1) {
        throw std::runtime_error{"readlink error: " + std::string{std::strerror(errno)}};
    } else if (n == 0) {
        throw std::runtime_error{"unable to determine executable path"};
    }

    buffer[n] = '\0';

    std::filesystem::path path{buffer};
    path = path.parent_path().parent_path() / "share";

    dbg("{}", path.string());
    return path;
}

std::filesystem::path find_cache_dir() {
    char* env_var{};

    bool xdg_var_set{true};

    env_var = std::getenv("XDG_CACHE_HOME");
    if (!env_var) {
        env_var     = std::getenv("HOME");
        xdg_var_set = false;
    }

    if (!env_var) {
        throw std::runtime_error{"could not resolve cache path"};
    }

    std::filesystem::path cache_dir{env_var};

    if (!xdg_var_set) {
        cache_dir /= ".cache";
    }

    dbg("{}", cache_dir.string());
    return cache_dir;
}

std::filesystem::path find_config_dir() {
    char* env_var{};

    bool xdg_var_set{true};

    env_var = std::getenv("XDG_CONFIG_HOME");
    if (!env_var) {
        env_var     = std::getenv("HOME");
        xdg_var_set = false;
    }

    if (!env_var) {
        throw std::runtime_error{"could not resolve config path"};
    }

    std::filesystem::path config_dir{env_var};

    if (!xdg_var_set) {
        config_dir /= ".config";
    }

    dbg("{}", config_dir.string());
    return config_dir;
}

std::optional<std::string> get_sys_lang_code() {
    const std::string lang = std::locale{""}.name();

    if (lang.size() < 2) {
        dbg("locale lookup failed (got '{}')", lang);
        return std::nullopt;
    }

    std::string code = lang.substr(0, 2);

    dbg("{}", code);
    return code;
}

} // namespace os

#endif
