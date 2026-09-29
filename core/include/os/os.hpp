// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#pragma once

#include <filesystem>

namespace os {

// Returns the installed application data path. This function exists to resolve
// differences in installation layout between platforms. The application relies
// on CMAKE_INSTALL_PREFIX to determine the installed path - it is written as
// DEF_APP_DATA_DIR_SYS compile definition. This works well in all cases except
// for NSIS, because NSIS installer allows the user to choose installation path.
// A custom installation directory does not match the path hard-coded by compile
// definitions. For this reason, on Windows, the application data directory
// must be determined in relation to the executable file path.
std::filesystem::path find_app_data_dir();

} // namespace os
