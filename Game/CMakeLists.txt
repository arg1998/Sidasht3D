cmake_minimum_required(VERSION 3.29)

project(Sidasht3D_Game LANGUAGES CXX)

set(CXX_STANDARD_REQUIRED 17)

file(GLOB_RECURSE GAME_CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp")

add_executable(${PROJECT_NAME} ${GAME_CPP_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Src")
