# SPDX-License-Identifier: AGPL-3.0-only
# Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

include_guard(GLOBAL)

set(app_data_dir ${CMAKE_BINARY_DIR}/app_data)
set(assets_dir "${app_data_dir}/assets")

file(MAKE_DIRECTORY ${app_data_dir} "${assets_dir}")

function(link_asset src_path)
    get_filename_component(base_name "${src_path}" NAME)

    set(dest_path "${assets_dir}/${base_name}")

    if(NOT EXISTS ${dest_path})
        execute_process(
            COMMAND
                ${CMAKE_COMMAND} -E create_symlink
                "${src_path}"
                "${dest_path}"
            COMMAND_ERROR_IS_FATAL ANY
        )
    endif()
endfunction()

set(ASSET_PATHS
    "${CMAKE_SOURCE_DIR}/assets/lang"
    "${CMAKE_SOURCE_DIR}/assets/mm.png"
    "${FONT_FILE_PATH}"
)

foreach(item IN LISTS ASSET_PATHS)
    link_asset("${item}")
endforeach()
