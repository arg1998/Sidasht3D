#include "Engine.hpp"
#include "S3D/Editor/Editor.hpp"
#include "S3D/Client/Client.hpp"

#include <raylib.h>

void s3d::Engine::StartEngine(EngineConfigs engineConfigs) {
    u32 raylibWindowConfigFlags = FLAG_MSAA_4X_HINT;
    u32 windowWidth = engineConfigs.mainWindow.width;
    u32 windowHeight = engineConfigs.mainWindow.height;

    switch (engineConfigs.mainWindow.mode) {
        case WindowMode::Resizable:
            raylibWindowConfigFlags |= FLAG_WINDOW_RESIZABLE;
            break;
        case WindowMode::Fullscreen:
            // This flag cuases monitor flickering and blackout and stalls in program for a few seconds
            // which is not ideal. The fix for this is to use ToggleBorderlessWindowed() after window creation
            // raylibWindowConfigFlags |= FLAG_WINDOW_RESIZABLE;
            windowWidth = GetMonitorWidth(0);
            windowHeight = GetMonitorHeight(0);
            break;
        default:
            break;
    }

    SetConfigFlags(raylibWindowConfigFlags);
    InitWindow(windowWidth, windowHeight, engineConfigs.mainWindow.name.c_str());
    if (engineConfigs.mainWindow.mode == WindowMode::Fullscreen) {
        ToggleBorderlessWindowed();
    }

    if (s3d::Editor::IsEditorEnabled()) {
        s3d::Editor::StartClientWithEditor();
    } else {
        s3d::Client::StartClient();
    }

    CloseWindow();
}