cmake_minimum_required(VERSION 3.16)
project(GameofLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x  
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SFML)


add_executable(GameofLife main.cpp)


target_link_libraries(GameofLife PRIVATE sfml-graphics)
