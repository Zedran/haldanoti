add_library(core STATIC
    src/game/Row.cpp
    src/game/helpers.cpp
    src/utils/Source.cpp
)

target_include_directories(core PUBLIC include)
