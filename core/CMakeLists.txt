set(CORE_SOURCES
    src/game/Game.cpp
    src/game/Row.cpp
    src/game/helpers.cpp
    src/ui/Binding.cpp
    src/ui/Box.cpp
    src/ui/Button.cpp
    src/ui/Label.cpp
    src/ui/Layout.cpp
    src/utils/Source.cpp
    src/utils/utils.cpp
)

add_library(core STATIC ${CORE_SOURCES})
target_include_directories(core PUBLIC include)
target_link_libraries(core PUBLIC SFML::Graphics)

if(MAKE_TESTS AND COVER)
    add_library(core_coverage ${CORE_SOURCES})
    target_include_directories(core_coverage PUBLIC include)
    target_link_libraries(core_coverage PUBLIC SFML::Graphics)

    target_compile_options(core_coverage PRIVATE -g --coverage)
    target_link_options(core_coverage PRIVATE --coverage)
endif()
