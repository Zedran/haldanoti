# SPDX-License-Identifier: AGPL-3.0-only
# Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

include_guard(GLOBAL)

include(FetchContent)

set(CATCH2_VERSION v3.16.1)

FetchContent_Declare(
    Catch2
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/catchorg/Catch2/archive/refs/tags/${CATCH2_VERSION}.tar.gz
    URL_HASH SHA256=d16bd1b8b2364918bd472cb216394acb93bde6784890df0d91bccfb3f28d777d
)
FetchContent_MakeAvailable(Catch2)
