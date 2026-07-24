# SPDX-License-Identifier: AGPL-3.0-only
# Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

include_guard(GLOBAL)

include(FetchContent)

set(FONT_VERSION 4.1)

set(FONT_HASH 9883fdd4a49d4fb66bd8177ba6625ef9a64aa45899767dde3d36aa425756b11e)

FetchContent_Declare(
    inter_font
    URL https://github.com/rsms/inter/releases/download/v${FONT_VERSION}/Inter-${FONT_VERSION}.zip
    URL_HASH SHA256=${FONT_HASH}
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
)
FetchContent_MakeAvailable(inter_font)

set(FONT_FILE_PATH "${inter_font_SOURCE_DIR}/InterVariable.ttf")
