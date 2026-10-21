# SPDX-License-Identifier: AGPL-3.0-only
# Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

include(ConfigUninstall)

set(TOP_DOC_FILES
    ${PROJECT_SOURCE_DIR}/LICENSE
    ${PROJECT_SOURCE_DIR}/NOTICE.md
    ${PROJECT_SOURCE_DIR}/README.md
    ${PROJECT_SOURCE_DIR}/SECURITY.md
)

set(BIN_DIR bin)

if(WIN32 AND CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "$ENV{ProgramFiles}/${PROJECT_NAME}" CACHE PATH "Install path" FORCE)
endif()

set(APP_DIR "share/${PROJECT_NAME}")

set(ASSETS_DIR_SRC ${PROJECT_SOURCE_DIR}/assets)
set(ASSETS_DIR_DEST ${APP_DIR})

set(DOC_DIR_SRC ${PROJECT_SOURCE_DIR}/docs)
set(DOC_DIR_DEST ${APP_DIR})

set(ASSETS_DIR ${APP_DIR}/assets)

install(TARGETS   ${PROJECT_NAME}   RUNTIME DESTINATION ${BIN_DIR})
install(FILES     ${TOP_DOC_FILES}  DESTINATION ${APP_DIR}        )
install(DIRECTORY ${ASSETS_DIR_SRC} DESTINATION ${ASSETS_DIR_DEST})
install(
    DIRECTORY     ${DOC_DIR_SRC}
    DESTINATION   ${DOC_DIR_DEST}
    PATTERN       "dev" EXCLUDE
)
install(FILES     ${FONT_FILE_PATH} DESTINATION ${ASSETS_DIR}     )

if(LINUX)
    set(DT_ENTRY "${CMAKE_BINARY_DIR}/platform/linux/haldanoti.desktop")

    set(BIN_PATH  "${CMAKE_INSTALL_PREFIX}/${BIN_DIR}/${PROJECT_NAME}")
    set(ICON_PATH "${CMAKE_INSTALL_PREFIX}/${ASSETS_DIR}/haldanoti.svg")

    configure_file(
        ${CMAKE_SOURCE_DIR}/platform/linux/haldanoti.desktop.in
        ${DT_ENTRY}
        @ONLY
    )

    install(FILES ${DT_ENTRY} DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
endif()
