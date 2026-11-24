cmake_minimum_required(VERSION 3.16)
project(TicTacToe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Download and build SFML automatically (no manual install needed)
include(FetchContent)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
    GIT_SHALLOW ON
)
FetchContent_MakeAvailable(SFML)

add_executable(tic_tac_toe
    src/main.cpp
    src/game.cpp
    src/difficulty.cpp
    src/scoreboard.cpp
    src/gui/gui.cpp
    src/audio/audio.cpp
)

target_include_directories(tic_tac_toe PRIVATE include)

target_link_libraries(tic_tac_toe PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# Copy assets (sounds) next to the exe
if(EXISTS "${CMAKE_SOURCE_DIR}/assets")
    add_custom_command(TARGET tic_tac_toe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:tic_tac_toe>/assets"
    )
endif()

# OpenAL dll is needed for sound on Windows
if(WIN32 AND EXISTS "${sfml_SOURCE_DIR}/extlibs/bin/x64/openal32.dll")
    add_custom_command(TARGET tic_tac_toe POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${sfml_SOURCE_DIR}/extlibs/bin/x64/openal32.dll"
            "$<TARGET_FILE_DIR:tic_tac_toe>"
    )
endif()