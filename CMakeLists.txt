cmake_minimum_required(VERSION 3.19.2)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 20)

include_directories(
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

add_executable(Minesweeper main.cpp ${INCLUDE_SRC} ${LIB_SRC})
