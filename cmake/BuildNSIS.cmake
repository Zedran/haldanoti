# SPDX-License-Identifier: AGPL-3.0-only
# Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

execute_process(
    COMMAND           git describe --tags --dirty
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    OUTPUT_VARIABLE   CPACK_PACKAGE_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE   GIT_TAG_RESULT
)

if (NOT GIT_TAG_RESULT EQUAL "0")
    message(FATAL_ERROR "Cannot package: Git failed with code ${GIT_TAG_RESULT}")
elseif (CPACK_PACKAGE_VERSION MATCHES "-g")
    message(FATAL_ERROR "Cannot package: untagged commit")
elseif (CPACK_PACKAGE_VERSION MATCHES "dirty")
    message(FATAL_ERROR "Cannot package: dirty working directory")
endif()

string(REGEX REPLACE "^v" "" CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION}")

set(CPACK_PACKAGE_NAME                         "mm"                                         )
set(CPACK_PACKAGE_VENDOR                       "Wojciech Głąb (github.com/Zedran)"          )
set(CPACK_PACKAGE_HOMEPAGE_URL                 "https://github.com/Zedran/mm"               )

set(CPACK_RESOURCE_FILE_LICENSE                "${PROJECT_SOURCE_DIR}/LICENSE"              )
set(CPACK_RESOURCE_FILE_README                 "${PROJECT_SOURCE_DIR}/README.md"            )

set(CPACK_PACKAGE_INSTALL_DIRECTORY            "${PROJECT_NAME}"                            )
set(CPACK_NSIS_DISPLAY_NAME                    "${CPACK_PACKAGE_NAME}"                      )
set(CPACK_NSIS_PACKAGE_NAME                    "${CPACK_PACKAGE_NAME}"                      )
set(CPACK_NSIS_CONTACT                         "${CPACK_PACKAGE_VENDOR}"                    )
set(CPACK_NSIS_URL_INFO_ABOUT                  "${CPACK_PACKAGE_HOMEPAGE_URL}"              )
set(CPACK_NSIS_MUI_ICON                        "${CMAKE_SOURCE_DIR}/platform/windows/mm.ico")
set(CPACK_NSIS_MODIFY_PATH                     OFF                                          )
set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON                                           )
set(CPACK_NSIS_IGNORE_COMPONENTS_PAGE          ON                                           )

include(CPack)
