// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#include <chrono>
#include <filesystem>
#include <ios>
#include <stdexcept>

#include "os/os.hpp"
#include "utils/Logger.hpp"
#include "utils/assets.hpp"

namespace utils {

Logger::Logger() {
    const std::filesystem::path cache_dir = os::find_cache_dir() / utils::APP_DIRNAME;

    if (!std::filesystem::exists(cache_dir)) {
        std::filesystem::create_directories(cache_dir);
    }

    constexpr auto LOG_FILE{"mm-game.log"};

    file_ = std::ofstream{cache_dir / LOG_FILE, std::ios::app};

    if (!file_.good()) {
        throw std::runtime_error{"unable to open log file"};
    }
}

Logger::~Logger() = default;

std::int64_t Logger::get_timestamp() {
    using namespace std::chrono;
    return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
}

Logger& Logger::instance() {
    static Logger instance;
    return instance;
}

void Logger::println(std::string_view version, std::string_view msg) {
    instance().file_ << "[ " << get_timestamp() << " ] (" << version << ") " << msg << '\n';
}

void Logger::println(std::string_view version, std::string_view msg, const std::exception& e) {
    instance().file_ << "[ " << get_timestamp() << " ] (" << version << ") " << msg << ": " << e.what() << '\n';
}

} // namespace utils
