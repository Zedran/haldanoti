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
    std::ifstream conf_file{utils::CONFIG_PATH};
    if (!conf_file.good()) {
        write_config(DEFAULT_CONFIG);
        return DEFAULT_CONFIG;
    }

    nlohmann::json j = nlohmann::json::parse(conf_file);
    return j.get<config::Config>();
}

void write_config(const Config& conf) {
    if (!std::filesystem::exists(utils::CONFIG_DIR)) {
        std::filesystem::create_directories(utils::CONFIG_DIR);
    }

    std::ofstream conf_file{utils::CONFIG_PATH, std::ios::trunc};
    if (!conf_file.good()) {
        throw std::runtime_error{"failed to open config file"};
    }

    constexpr int JSON_INDENT = 4;

    const nlohmann::json j = conf;
    conf_file << j.dump(JSON_INDENT);
}

} // namespace config
