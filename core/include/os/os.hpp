// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <filesystem>
#include <optional>
#include <string>

namespace os {

// Returns application data directory path (/share/), determined from
// the executable file position.
std::filesystem::path find_app_data_dir();

// Returns user cache directory.
std::filesystem::path find_cache_dir();

// Returns user config directory.
std::filesystem::path find_config_dir();

// Returns a 2-letter language code retrieved from system's default locale name.
// Returns nullopt if querying locale fails.
std::optional<std::string> get_sys_lang_code();

} // namespace os
