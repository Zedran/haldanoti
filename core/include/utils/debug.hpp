// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#if defined(NDEBUG)

#define dbg(fmt, ...) ((void)0)

#else

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <format>
#include <iostream>
#include <source_location>
#include <span>
#include <string>
#include <string_view>
#include <utility>

// A wrapper for debug::write that captures source_location at the call site.
// Accepts a format_string along with an arbitrary number of arguments
// and prints the formatted log entry to stderr. This macro does not
// display non-ASCII characters correctly, but such characters are
// only used for presentation purposes and do not need to examined.
#define dbg(fmt, ...) debug::write(std::source_location::current(), fmt __VA_OPT__(, ) __VA_ARGS__)

template <std::size_t Extent>
struct std::formatter<std::span<const int, Extent>, char> {
    template <class ParseContext>
    constexpr ParseContext::iterator parse(ParseContext& ctx) {
        return ctx.begin();
    }

    template <class FmtContext>
    FmtContext::iterator format(std::span<const int> s, FmtContext& ctx) const {
        std::string str{'['};

        for (std::size_t i = 0; i < s.size(); i++) {
            str += std::to_string(s[i]);

            if (i < s.size() - 1) {
                str += ", ";
            }
        }
        str += ']';

        return std::ranges::copy(std::move(str), ctx.out()).out;
    }
};

namespace debug {

// Constructs a log entry from the specified source_location, format_string
// and an arbitrary number of arguments. The resulting entry is printed
// to stderr. This function is only available in debug build, therefore
// it should not be called directly. Use the dbg macro instead.
template <typename... Args>
inline void write(std::source_location loc, std::format_string<Args...> fmt, Args&&... args) {
#if defined(_WIN32)
    constexpr std::string_view TIME_COLOR = "";
    constexpr std::string_view FUNC_COLOR = "";
    constexpr std::string_view RST_COLOR  = "";
#else
    constexpr std::string_view TIME_COLOR = "\033[36m";
    constexpr std::string_view FUNC_COLOR = "\033[31m";
    constexpr std::string_view RST_COLOR  = "\033[0m";
#endif

    using namespace std::chrono;

    const time_point time_utc = floor<seconds>(system_clock::now());
    const zoned_time time_local{current_zone(), time_utc};

    std::cerr << std::format(
        "{}{:%H:%M:%S} {}{} {}{}\n",
        TIME_COLOR, time_local,
        FUNC_COLOR, loc.function_name(),
        RST_COLOR, std::format(fmt, std::forward<Args>(args)...)
    );
}

} // namespace debug

#endif
