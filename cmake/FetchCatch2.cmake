# SPDX-License-Identifier: AGPL-3.0-only
# Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

include_guard(GLOBAL)

include(FetchContent)

set(CATCH2_VERSION v3.16.0)

FetchContent_Declare(
    Catch2
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/catchorg/Catch2/archive/refs/tags/${CATCH2_VERSION}.tar.gz
    URL_HASH SHA256=0957cae5821b17ce07f0833aaa52b5137643a8382203221f363a8303c109af34
)
FetchContent_MakeAvailable(Catch2)
