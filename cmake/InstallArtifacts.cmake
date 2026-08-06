# SPDX-License-Identifier: AGPL-3.0-only
# Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

include(ConfigUninstall)

set(ASSET_FILES
    ${FONT_FILE_PATH}
    ${CMAKE_SOURCE_DIR}/assets/mm.png
    ${CMAKE_SOURCE_DIR}/assets/mm.svg
)

set(LANG_DIR ${PROJECT_SOURCE_DIR}/assets/lang)

set(DOC_FILES
    ${PROJECT_SOURCE_DIR}/LICENSE
    ${PROJECT_SOURCE_DIR}/NOTICE.md
    ${PROJECT_SOURCE_DIR}/README.md
)

set(LIC_FILES
    ${PROJECT_SOURCE_DIR}/docs/licenses/Inter.txt
    ${PROJECT_SOURCE_DIR}/docs/licenses/SFML.txt
)

set(BIN_DIR bin)

set(APP_DIR "share/${PROJECT_NAME}")

set(ASSETS_DIR ${APP_DIR}/assets)
set(DOC_DIR ${APP_DIR})
set(LIC_DIR ${APP_DIR}/docs/licenses)

install(TARGETS ${PROJECT_NAME} DESTINATION ${BIN_DIR}   )
install(FILES   ${ASSET_FILES}  DESTINATION ${ASSETS_DIR})
install(FILES   ${DOC_FILES}    DESTINATION ${DOC_DIR}   )
install(FILES   ${LIC_FILES}    DESTINATION ${LIC_DIR}   )
install(DIRECTORY ${LANG_DIR}   DESTINATION ${ASSETS_DIR})

target_compile_definitions(${PROJECT_NAME} PUBLIC
    FONT_FILE_PATH_SYS="${CMAKE_INSTALL_PREFIX}/${ASSETS_DIR}/InterVariable.ttf"
    ICON_FILE_PATH_SYS="${CMAKE_INSTALL_PREFIX}/${ASSETS_DIR}/mm.png"
    LANG_DIR_PATH_SYS="${CMAKE_INSTALL_PREFIX}/${ASSETS_DIR}/lang"
)

if(LINUX)
    set(DT_ENTRY "${CMAKE_BINARY_DIR}/platform/linux/mm-game.desktop")

    set(BIN_PATH  "${CMAKE_INSTALL_PREFIX}/${BIN_DIR}/${PROJECT_NAME}")
    set(ICON_PATH "${CMAKE_INSTALL_PREFIX}/${ASSETS_DIR}/mm.svg"      )

    configure_file(
        ${CMAKE_SOURCE_DIR}/platform/linux/mm-game.desktop.in
        ${DT_ENTRY}
        @ONLY
    )

    install(FILES ${DT_ENTRY} DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
endif()
