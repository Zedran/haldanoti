# SPDX-License-Identifier: AGPL-3.0-only
# Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

include_guard(GLOBAL)

find_package(nlohmann_json 3.12.0)

if(NOT nlohmann_json_FOUND)
    include(FetchContent)

    set(NLOHMANN_JSON_HASH 55f93686c01528224f448c19128836e7df245f72) # v3.12.0

    FetchContent_Declare(nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG ${NLOHMANN_JSON_HASH}
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM
    )
    FetchContent_MakeAvailable(nlohmann_json)
endif()
