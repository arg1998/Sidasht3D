#include <S3D/Entry/Entry.hpp>
#include <S3D/Engine/Engine.hpp>
#include <S3D/Profiler/Profiler.hpp>

#include <iostream>

void s3d::GameMain(PlatformOS pltOS) {
    ZoneScopedN("GameMain()");
    std::cout << "Hello Sidasht3D Engine! " << std::endl;

    s3d::Engine::EngineConfigs engineConf;
    engineConf.mainWindow.mode = s3d::Engine::WindowMode::Fullscreen;
    engineConf.mainWindow.width = 1280;
    engineConf.mainWindow.height = 720;
    engineConf.mainWindow.name = "Secret Game";

    s3d::Engine::StartEngine(engineConf);
}