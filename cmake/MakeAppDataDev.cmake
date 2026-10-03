# SPDX-License-Identifier: AGPL-3.0-only
# Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

include_guard(GLOBAL)

set(app_data_dir "${CMAKE_BINARY_DIR}/share/${PROJECT_NAME}")

set(assets_dir_src  "${CMAKE_SOURCE_DIR}/assets")
set(assets_dir_dest "${app_data_dir}/assets")

file(MAKE_DIRECTORY "${app_data_dir}")

execute_process(
    COMMAND
        ${CMAKE_COMMAND} -E copy_directory_if_different
        "${assets_dir_src}"
        "${assets_dir_dest}"
    COMMAND_ERROR_IS_FATAL ANY
)

get_filename_component(base_font_name "${FONT_FILE_PATH}" NAME)

execute_process(
    COMMAND
        ${CMAKE_COMMAND} -E copy_if_different
        "${FONT_FILE_PATH}"
        "${assets_dir_dest}/${base_font_name}"
    COMMAND_ERROR_IS_FATAL ANY
)
