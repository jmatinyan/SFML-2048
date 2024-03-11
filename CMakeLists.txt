cmake_minimum_required(VERSION 3.23)
project(2048)

set(CMAKE_CXX_STANDARD 14)

add_executable(2048 main.cpp Game.cpp Game.h MainMenu.cpp MainMenu.h Button.cpp Button.h Board.cpp Board.h Tile.cpp Tile.h GameColors.cpp GameColors.h GameSizes.h)

target_link_libraries(2048 sfml-graphics sfml-audio)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
