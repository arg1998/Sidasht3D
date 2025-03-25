cmake_minimum_required(VERSION 3.18)

project(Sidasht3D LANGUAGES CXX)

set(CXX_STANDARD_REQUIRED 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")


set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo;RelWithTracyProfiler" CACHE STRING "Available build types" FORCE)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Engine")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Game")



target_link_libraries(Sidasht3D_Game PRIVATE Sidasht3D_Engine)

