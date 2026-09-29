// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <filesystem>
#include <fstream>
#include <optional>
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

namespace utils {

// Application directory name. Created in user's cache and config directories.
static constexpr std::string_view APP_DIRNAME{"mm-game"};

// Location of the user config directory.
static const std::filesystem::path CONFIG_DIR = os::find_config_dir() / APP_DIRNAME;

// Name of the config file.
static const std::filesystem::path CONFIG_FNAME{"mm.json"};

// Full path to config file.
static const std::filesystem::path CONFIG_PATH = CONFIG_DIR / CONFIG_FNAME;

// System application data path.
static const std::filesystem::path APP_DATA_SYS_PATH{os::find_app_data_dir()};

// Name of the assets directory located in the APP_DATA_DIR.
static const std::filesystem::path ASSETS_DIRNAME{"assets"};

// Language files subdirectory. Combine with APP_DATA_DIR/ASSETS_DIRNAME.
static const std::filesystem::path LANG_DIRNAME{"lang"};

// 2-letter code of the default language.
static constexpr std::string_view DEFAULT_LANG_CODE{"en"};

// Returns a list of available language filenames without extensions.
std::vector<sf::String> get_lang_fnames();

// Returns a 2-letter language code retrieved from system's default locale name.
// Returns nullopt if querying locale fails.
std::optional<std::string> get_sys_lang_code();

// Returns a list of file paths in dir.
std::vector<std::filesystem::path> list_files(const std::filesystem::path& dir);

// Iterates over the list of possible asset file locations (system installation
// then dev directory) and returns T constructed from the first found file.
//
// Accepts a relative path to the asset file. It is appended to
// APP_DATA_DIR/ASSETS_DIRNAME.
//
// Throws runtime_error if rel_path is empty or is an absolute path.
template <typename T>
    requires std::is_same_v<T, sf::Font> ||
             std::is_same_v<T, sf::Image> ||
             std::is_same_v<T, std::ifstream>
T load_asset(std::filesystem::path rel_path) {
    if (rel_path.empty()) {
        throw std::runtime_error{"asset relative path is empty"};
    }

    if (!rel_path.is_relative()) {
        throw std::runtime_error{"path '" + rel_path.string() + "' is not relative"};
    }

    rel_path = ASSETS_DIRNAME / rel_path;

    for (const auto& d : {APP_DATA_SYS_PATH, std::filesystem::path{DEF_APP_DATA_DIR_DEV}}) {
        const std::filesystem::path p = d / rel_path;

        try {
            if (!std::filesystem::exists(p)) {
                continue;
            }

            if constexpr (std::is_same_v<T, sf::Font>) {
                sf::Font font{p};
                font.setSmooth(false);
                return font;
            } else if constexpr (std::is_same_v<T, sf::Image>) {
                sf::Image img;
                if (img.loadFromFile(p)) {
                    return img;
                }
            } else if constexpr (std::is_same_v<T, std::ifstream>) {
                std::ifstream f{std::filesystem::path{p}};
                if (f.good()) {
                    return f;
                }
            }
        } catch (const sf::Exception&) {
        }
    }
    throw std::runtime_error{"unable to load asset '" + rel_path.string() + '\''};
}

// Returns a lang::Lang struct with game text translations corresponding to the
// system locale or lang::DEFAULT_LANG if suitable translation file is not
// found. Throws upon encountering JSON parsing errors.
//
// lang_fname is the name of the desired translation file. Translation files
// are named with the lower-case 2-letter country code (ISO 639). The function
// expects the file to have the '.json' extension and it will be appended
// to lang_fname if missing.
lang::Lang load_language(std::string lang_fname);

} // namespace utils
