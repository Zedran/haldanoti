// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <cstdint>
#include <exception>
#include <fstream>
#include <string_view>

namespace utils {

// This singleton is designed to log unrecoverable program errors.
// Its functionality is very minimal and targeted, because exceptions
// it logs should never be thrown under normal conditions.
class Logger {
public:
    // Prints version information and message to the log file.
    static void println(std::string_view version, std::string_view msg);

    // Prints version information, message and exception information to the log file.
    static void println(std::string_view version, std::string_view msg, const std::exception& e);

private:
    // Log file written to the user's cache directory.
    std::ofstream file_;

    // Returns Unix timestamp.
    static std::int64_t get_timestamp();

    static Logger& instance();

    Logger();

    Logger(const Logger& other)            = delete;
    Logger& operator=(const Logger& other) = delete;

    ~Logger();
};

} // namespace utils
