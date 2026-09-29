// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#if defined(__linux__)

#include "os/os.hpp"

namespace os {

std::filesystem::path find_app_data_dir() {
    return std::filesystem::path{DEF_APP_DATA_DIR_SYS};
}

} // namespace os

#endif
