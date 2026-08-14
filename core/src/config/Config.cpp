// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <filesystem>
#include <fstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include "config/Config.hpp"
#include "config/default_config.hpp"
#include "utils/assets.hpp"

namespace config {

config::Config read_config() {
    constexpr auto CONF_FNAME{"mm.json"};

    const auto conf_path = utils::CONFIG_DIR / CONF_FNAME;

    std::ifstream conf_file{conf_path};
    if (!conf_file.good()) {
        write_config(conf_path, DEFAULT_CONFIG);
        return DEFAULT_CONFIG;
    }

    nlohmann::json j = nlohmann::json::parse(conf_file);
    return j.get<config::Config>();
}

void write_config(const std::filesystem::path& path, const Config& conf) {
    if (!std::filesystem::exists(path.parent_path())) {
        std::filesystem::create_directories(path.parent_path());
    }

    std::ofstream conf_file{path, std::ios::trunc};
    if (!conf_file.good()) {
        throw std::runtime_error{"failed to open config file"};
    }

    constexpr int JSON_INDENT = 4;

    const nlohmann::json j = conf;
    conf_file << j.dump(JSON_INDENT);
}

} // namespace config
