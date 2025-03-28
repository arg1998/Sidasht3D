include(FetchContent)


set(RAYLIB_VERSION 5.5)
set(TRACY_VERSION 0.11.1)
set(FMT_VERSION 11.1.4)



FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL "https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz"
    FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(raylib)
target_include_directories(raylib PUBLIC 
    ${raylib_SOURCE_DIR}/src
    ${raylib_SOURCE_DIR}/src/external/glfw/include
)


FetchContent_Declare(
    tracy
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL "https://github.com/wolfpld/tracy/archive/refs/tags/v${TRACY_VERSION}.tar.gz"
    FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(tracy)



FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking  
)
FetchContent_MakeAvailable(imgui)
add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC 
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    # pull some of the external dependency from raylib
    ${raylib_SOURCE_DIR}/src
    ${raylib_SOURCE_DIR}/src/external/glfw/inlcude
)

target_link_libraries(imgui PUBLIC raylib)


FetchContent_Declare(
    rlimgui
    GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
    GIT_TAG main
)
FetchContent_MakeAvailable(rlimgui)
add_library(rlimgui STATIC ${rlimgui_SOURCE_DIR}/rlImGui.cpp)
target_include_directories(rlimgui PUBLIC 
    ${rlimgui_SOURCE_DIR}
    # dear imgui headers 
    ${imgui_SOURCE_DIR}
    # raylib headers
    ${raylib_SOURCE_DIR}/src
)
target_link_libraries(rlimgui PUBLIC raylib imgui)


FetchContent_Declare(
    cppfonts
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    GIT_REPOSITORY "https://github.com/juliettef/IconFontCppHeaders.git"
    GIT_TAG main
)
FetchContent_MakeAvailable(cppfonts)
add_library(cppfonts INTERFACE)
target_include_directories(cppfonts INTERFACE ${cppfonts_SOURCE_DIR})


FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG        123913715afeb8a437e6388b4473fcc4753e1c9a) # 11.1.4
FetchContent_MakeAvailable(fmt)


# Set RelWithTracyProfiler build type settings
set(CMAKE_CXX_FLAGS_RELWITHTRACYPROFILER "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -fno-omit-frame-pointer -Wno-inline-new-delete -DTRACY_ENABLE" CACHE STRING "Compiler flags when profiling" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELWITHTRACYPROFILER "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO} -rdynamic" CACHE STRING "Linker flags when profiling" FORCE)
set(CMAKE_SHARED_LINKER_FLAGS_RELWITHTRACYPROFILER "${CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO} -rdynamic" CACHE STRING "Shared libs flags when profiling" FORCE)

if(CMAKE_BUILD_TYPE STREQUAL "RelWithTracyProfiler")
    option(TRACY_ENABLE "Enable Tracy Profiler" ON)
    set(TRACY_ENABLE ON)
    message("Tracy Profiler is ON")
else()
    option(TRACY_ENABLE "Enable Tracy Profiler" OFF)
    set(TRACY_ENABLE OFF)
    message("Tracy Profiler is OFF")
endif()

target_compile_options(TracyClient PRIVATE -Wno-error) 


