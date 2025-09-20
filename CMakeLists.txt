cmake_minimum_required(VERSION 3.25)

project(Sidasht3D LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Bin")
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Bin")
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Bin")


set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo;RelWithTracyProfiler" CACHE STRING "Available build types" FORCE)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Engine")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Game")



target_link_libraries(Sidasht3D_Game PRIVATE Sidasht3D_Engine)


add_custom_target(ENGINE_ASSET_TRANSFER ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Engine/Assets"
        "${CMAKE_SOURCE_DIR}/Bin/Assets"
    COMMENT "Copying Engine Assets to Bin/ Directory..."
)

add_custom_target(GAME_ASSET_TRANSFER ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Game/Assets"
        "${CMAKE_SOURCE_DIR}/Bin/Assets"
    COMMENT "Copying Game Assets to Bin/ Directory..."
)

