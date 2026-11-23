cmake_minimum_required(VERSION 3.16)
project(TicTacToe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(tic_tac_toe
    main.cpp
    game.cpp
    difficulty.cpp
    scoreboard.cpp
)

target_link_libraries(tic_tac_toe PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

file(COPY assets DESTINATION "${CMAKE_BINARY_DIR}")