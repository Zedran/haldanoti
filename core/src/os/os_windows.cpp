// SPDX-License-Identifier: AGPL-3.0-only
// Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

#if defined(_WIN32)

#include <stdexcept>
#include <windows.h>

#include "os/os.hpp"

namespace os {

std::filesystem::path find_app_data_dir() {
    // Reference: https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getmodulefilenamew

    wchar_t buffer[MAX_PATH];

    const DWORD n = GetModuleFileNameW(nullptr, buffer, MAX_PATH);
    if (n == 0) {
        throw std::runtime_error{"unable to determine executable path"};
    }

    return std::filesystem::path{buffer}.parent_path().parent_path();
}

} // namespace os

#endif
