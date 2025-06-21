#cmake_minimum_required(VERSION 3.31)
#project(MonkeyTyper)
#
#set(CMAKE_CXX_STANDARD 20)
#
#add_executable(MonkeyTyper main.cpp)

cmake_minimum_required(VERSION 3.25)
project (MonkeyTyper)

include (FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)

set (CHAKE_CXX_STANDARD 20)

add_executable(MonkeyTyper main.cpp
        game.cpp
        game.h
        word.cpp
        word.h
        menu.cpp
        menu.h)

target_link_Libraries(MonkeyTyper sfml-graphics)