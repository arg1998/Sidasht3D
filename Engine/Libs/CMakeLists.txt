include(FetchContent)


set(RAYLIB_VERSION 5.5)
set(TRACY_VERSION 0.11.1)


FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL "https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz"
    FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(raylib)


FetchContent_Declare(
    tracy
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL "https://github.com/wolfpld/tracy/archive/refs/tags/v${TRACY_VERSION}.tar.gz"
    FIND_PACKAGE_ARGS
)
FetchContent_MakeAvailable(tracy)



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


