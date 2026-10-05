// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Exception.hpp>
#include <SFML/System/String.hpp>

#include "lang/Lang.hpp"
#include "os/os.hpp"
#include "theme/Theme.hpp"

namespace utils {

// Application directory name. Created in user's cache and config directories.
inline constexpr std::string_view APP_DIRNAME{"mm-game"};

// Location of the user config directory.
inline const std::filesystem::path CONFIG_DIR = os::find_config_dir() / APP_DIRNAME;

// Name of the config file.
inline const std::filesystem::path CONFIG_FNAME{"mm.json"};

// Full path to config file.
inline const std::filesystem::path CONFIG_PATH = CONFIG_DIR / CONFIG_FNAME;

// Application data path.
inline const std::filesystem::path APP_DATA_DIR = os::find_app_data_dir() / APP_DIRNAME;

// Name of the assets directory located in the APP_DATA_DIR.
inline const std::filesystem::path ASSETS_DIRNAME{"assets"};

// Language files subdirectory. Combine with APP_DATA_DIR/ASSETS_DIRNAME.
inline const std::filesystem::path LANG_DIRNAME{"lang"};

// Theme files subdirectory. Combine with APP_DATA_DIR/ASSETS_DIRNAME.
inline const std::filesystem::path THEME_DIRNAME{"theme"};

// 2-letter code of the default language.
inline constexpr std::string_view DEFAULT_LANG_CODE{"en"};

// Name of the default theme.
inline constexpr std::string_view DEFAULT_THEME{"default"};

// Returns a list of available language filenames without extensions.
std::vector<sf::String> get_lang_fnames();

// Returns a list of available theme filenames without extensions.
std::vector<sf::String> get_theme_fnames();

// Returns a list of file paths in dir.
std::vector<std::filesystem::path> list_files(const std::filesystem::path& dir);

// Returns T constructed from the asset file. If path is relative,
// it is appended to APP_DATA_DIR/ASSETS_DIRNAME.
template <typename T>
    requires std::is_same_v<T, sf::Font> ||
             std::is_same_v<T, sf::Image> ||
             std::is_same_v<T, std::ifstream>
T load_asset(std::filesystem::path path) {
    if (path.empty()) {
        throw std::runtime_error{"asset relative path is empty"};
    }

    if (path.is_relative()) {
        path = APP_DATA_DIR / ASSETS_DIRNAME / path;
    }

    if constexpr (std::is_same_v<T, sf::Font>) {
        sf::Font font{path};
        font.setSmooth(false);
        return font;
    }

    if constexpr (std::is_same_v<T, sf::Image>) {
        return sf::Image{path};
    }

    if constexpr (std::is_same_v<T, std::ifstream>) {
        std::ifstream f{std::filesystem::path{path}};
        if (!f.good()) {
            throw std::runtime_error{"unable to load file '" + path.string() + '\''};
        }
        return f;
    }
}

// Returns a lang::Lang struct with game text translations corresponding to the
// chosen language or default language if suitable translation file is not
// found. Throws upon encountering JSON parsing errors or problems with
// the file.
//
// lang_fname is the name of the desired translation file. Translation files
// are named with the lower-case 2-letter country code (ISO 639). The function
// expects the file to have the '.json' extension and it will be appended
// to lang_fname if missing.
lang::Lang load_language(std::string lang_fname);

// Returns a theme::Theme struct read from the received file name or the default
// theme if file is missing. Throws upon encountering JSON parsing errors
// or problems with fallback file.
//
// The function expects filenames to have the '.json' extension and it will be
// appended to theme_fname if missing.
theme::Theme load_theme(std::string theme_fname);

} // namespace utils
