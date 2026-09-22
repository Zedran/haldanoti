# SPDX-License-Identifier: AGPL-3.0-only
# Copyright (C) 2026 Wojciech Głąb (github.com/Zedran)

set(CORE_SOURCES
    src/app/App.cpp
    src/app/Board.cpp
    src/app/CodeButton.cpp
    src/app/FeedbackLabel.cpp
    src/app/GameRow.cpp
    src/app/Message.cpp
    src/app/SecretRow.cpp
    src/app/Settings.cpp
    src/app/Toolbar.cpp
    src/app/Window.cpp
    src/config/Config.cpp
    src/game/Game.cpp
    src/game/Row.cpp
    src/game/helpers.cpp
    src/ui/Binding.cpp
    src/ui/Blank.cpp
    src/ui/Box.cpp
    src/ui/Button.cpp
    src/ui/Checkbox.cpp
    src/ui/Label.cpp
    src/ui/Layout.cpp
    src/ui/Selector.cpp
    src/utils/Source.cpp
    src/utils/assets.cpp
    src/utils/json.cpp
    src/utils/utils.cpp
)

add_library(core STATIC ${CORE_SOURCES})
target_include_directories(core PUBLIC include)
target_link_libraries(core PUBLIC
    core_defs
    SFML::System
    SFML::Window
    SFML::Graphics
    nlohmann_json::nlohmann_json
)

if(MAKE_TESTS AND COVER)
    add_library(core_coverage ${CORE_SOURCES})
    target_include_directories(core_coverage PUBLIC include)
    target_link_libraries(core_coverage PUBLIC
        core_defs
        SFML::System
        SFML::Window
        SFML::Graphics
        nlohmann_json::nlohmann_json
    )

    target_compile_options(core_coverage PRIVATE -g --coverage)
    target_link_options(core_coverage PRIVATE --coverage)
endif()
