include_guard(GLOBAL)

include(FetchContent)

set(SFML_VERSION 8835b6b955c96fa1ad1278a8dae6f05c4143effc) # 3.1.0

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG ${SFML_VERSION}
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)
