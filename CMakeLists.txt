cmake_minimum_required(VERSION 3.30)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)

if (NOT TARGET SFML)
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://gitee.com/realtest/SFML.git
            GIT_TAG 3.0.0
            GIT_SHALLOW ON
            EXCLUDE_FROM_ALL
            SYSTEM)
    FetchContent_MakeAvailable(SFML)
endif ()

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib
)
link_directories(${PROJECT_SOURCE_DIR}/lib)

file(GLOB INCLUDE_SRC
        "${PROJECT_SOURCE_DIR}/include/*.h"
)
file(GLOB LIB_SRC
        "${PROJECT_SOURCE_DIR}/lib/*.cpp"
)

add_executable(Minesweeper main.cpp config.h ${INCLUDE_SRC} ${LIB_SRC})
target_link_libraries(Minesweeper PRIVATE
        SFML::Audio
        SFML::System
)
