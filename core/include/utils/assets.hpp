// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <array>
#include <filesystem>
#include <fstream>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Exception.hpp>
#include <SFML/System/String.hpp>

#include "lang/Lang.hpp"

namespace utils {

// Returns user config directory.
std::filesystem::path find_config_dir();

// Location of the user config directory.
static const std::filesystem::path CONFIG_DIR = utils::find_config_dir();

// Name of the config file.
static const std::filesystem::path CONFIG_FNAME{"mm.json"};

// Full path to config file.
static const std::filesystem::path CONFIG_PATH = CONFIG_DIR / CONFIG_FNAME;

// Returns a list of available language filenames without extensions.
std::vector<sf::String> get_lang_fnames();

// Returns a 2-letter language code retrieved from system's default locale name.
std::string get_system_language();

// Returns a list of file paths in dir.
std::vector<std::filesystem::path> list_files(const std::filesystem::path& dir);

// Iterates over the list of possible asset file locations and initializes
// T using the first found file. Throws runtime_error if no file was found.
template <typename T>
    requires std::is_same_v<T, sf::Font> ||
             std::is_same_v<T, sf::Image> ||
             std::is_same_v<T, std::ifstream>
T load_asset(std::initializer_list<std::string_view> paths) {
    for (const auto& p : paths) {
        try {
            if constexpr (std::is_same_v<T, sf::Font>) {
                return sf::Font{p};
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
    throw std::runtime_error{"unable to load asset"};
}

// Returns a lang::Lang struct with game text translations corresponding to the
// system locale or lang::DEFAULT_LANG if suitable translation file is not
// found. Throws upon encountering JSON parsing errors.
//
// lang_dirs is an array containing possible locations of the lang directory.
// lang_fname is the name of the preferred translation file. Translation files
// are named with the lower-case 2-letter country code (ISO 639). The function
// expects the file to have the '.json' extension and it will be appended
// to lang_fname if missing.
lang::Lang load_language(
    std::array<std::string, 2> lang_dirs,
    std::string                lang_fname
);

} // namespace utils
