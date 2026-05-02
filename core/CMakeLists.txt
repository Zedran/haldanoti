set(CORE_SOURCES
    src/game/Game.cpp
    src/game/Row.cpp
    src/game/helpers.cpp
    src/utils/Source.cpp
)

add_library(core STATIC ${CORE_SOURCES})
target_include_directories(core PUBLIC include)

if(MAKE_TESTS AND COVER)
    add_library(core_coverage ${CORE_SOURCES})
    target_include_directories(core_coverage PUBLIC include)

    target_compile_options(core_coverage PRIVATE -g --coverage)
    target_link_options(core_coverage PRIVATE --coverage)
endif()
