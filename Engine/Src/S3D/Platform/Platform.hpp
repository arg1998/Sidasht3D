#pragma once

#include "S3D/Definitions.hpp"


namespace s3d
{
    enum class PlatformOS {
        Windows, 
        MacOS,
        Linux
    };


    PlatformOS GetPlatformOperatingSystem();
    
} // namespace s3d
