cmake_minimum_required(VERSION 3.18)

project(Sidasht3D_Engine LANGUAGES CXX)
set(CXX_STANDARD_REQUIRED 17)

file(GLOB_RECURSE ENGINE_CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Src/S3D/*.cpp")

add_library(${PROJECT_NAME} STATIC ${ENGINE_CPP_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Src/")


set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin")
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin")





set(BUILD_SHARED_LIBS OFF)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Libs")

target_link_libraries(${PROJECT_NAME} raylib)
target_link_libraries(${PROJECT_NAME} TracyClient)

