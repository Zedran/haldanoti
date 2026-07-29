# SPDX-License-Identifier: AGPL-3.0-only
# Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

include(ConfigUninstall)

set(ASSET_FILES
    ${FONT_FILE_PATH}
    ${CMAKE_SOURCE_DIR}/assets/mm.png
    ${CMAKE_SOURCE_DIR}/assets/mm.svg
)

set(DOC_FILES
    ${PROJECT_SOURCE_DIR}/LICENSE
    ${PROJECT_SOURCE_DIR}/NOTICE.md
    ${PROJECT_SOURCE_DIR}/README.md
)

set(BIN_DIR bin)

set(APP_DIR "share/${PROJECT_NAME}")

set(ASSETS_DIR ${APP_DIR}/assets)
set(DOC_DIR ${APP_DIR})

install(TARGETS ${PROJECT_NAME} DESTINATION ${BIN_DIR}   )
install(FILES   ${ASSET_FILES}  DESTINATION ${ASSETS_DIR})
install(FILES   ${DOC_FILES}    DESTINATION ${DOC_DIR}   )

target_compile_definitions(${PROJECT_NAME} PUBLIC
    FONT_FILE_PATH_SYS="${CMAKE_INSTALL_PREFIX}/${ASSETS_DIR}/InterVariable.ttf"
    ICON_FILE_PATH_SYS="${CMAKE_INSTALL_PREFIX}/${ASSETS_DIR}/mm.png"
)
