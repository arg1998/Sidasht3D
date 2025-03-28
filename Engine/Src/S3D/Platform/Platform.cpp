#include "Platform.hpp"

using namespace s3d;

PlatformOS s3d::GetPlatformOperatingSystem() {
    #if defined(S3D_PLATFORM_WINDOWS)
        return PlatformOS::Windows;
    #elif defined(S3D_PLATFORM_MACOS)
        return PlatformOS::MacOS;
    #elif defined(S3D_PLATFORM_LINUX)
        return PlatformOS::Linux
    #else
    //  TODO: throw an error 
    #endif
}