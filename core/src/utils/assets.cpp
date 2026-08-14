// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <cstdlib>
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

lang::Lang load_language(
    std::array<std::string, 2> lang_dirs,
    std::optional<std::string> lang_fname
) {
    std::string pref_lang = lang_fname ? lang_fname.value() : std::locale{""}.name().substr(0, 2);

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
