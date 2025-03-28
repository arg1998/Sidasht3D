#pragma once

#include "S3D/Definitions.hpp"

#include <string>

namespace s3d {
namespace Engine {

enum class WindowMode {
    Resizable,
    Fullscreen
};

enum class FpsMode {
    Capped,
    CappedVSync,
    Uncapped

};

struct Window {
    u32 width{0};
    u32 height{0};
    std::string name{"Sidasht3D Engine"};
    WindowMode mode{WindowMode::Resizable};
};

struct EngineConfigs {
    Window mainWindow;
};

}  // namespace Engine
}  // namespace s3d
