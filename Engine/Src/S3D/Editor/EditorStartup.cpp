#include "Editor.hpp"
#include "S3D/Profiler/Profiler.hpp"
#include "S3D/Logging/Logging.hpp"

#include <raylib.h>
#include <raymath.h>
#include <imgui.h>
#include <rlImGui.h>

bool Quit = false;
bool ImGuiDemoOpen = true;

// DPI scaling functions
float ScaleToDPIF(float value) {
    return GetWindowScaleDPI().x * value;
}

int ScaleToDPII(int value) {
    return int(GetWindowScaleDPI().x * value);
}

class DocumentWindow {
   public:
    bool Open = false;

    RenderTexture ViewTexture;

    virtual void Setup() = 0;
    virtual void Shutdown() = 0;
    virtual void Show() = 0;
    virtual void Update() = 0;

    bool Focused = false;

    Rectangle ContentRect = {0};
};

class PlaygroundViewerWindow : public DocumentWindow {
   public:
    void Setup() override {}

    void Show() override {
        if (ImGui::Begin("Playground")) {
            if (ImGui::Button("Test Logging")) {
                LOG_DEBUG("Debugging value: {}", 42);
                LOG_INFO("Application started successfully.");
                LOG_WARNING("Disk space is low: {} GB left", 2);
                LOG_ERROR("Failed to load configuration file: {}", "config.yaml");
                LOG_FATAL("Critical system failure!");
            }
        }
        ImGui::End();
    }

    void Update() override {}

    Texture ImageTexture;
    Camera2D Camera = {0};

    Vector2 LastMousePos = {0};
    Vector2 LastTarget = {0};
    bool Dragging = false;

    bool DirtyScene = false;

    enum class ToolMode {
        None,
        Move,
    };

    ToolMode CurrentToolMode = ToolMode::None;

    void UpdateRenderTexture() {
        BeginTextureMode(ViewTexture);
        ClearBackground(BLUE);

        // camera with our view offset with a world origin of 0,0
        BeginMode2D(Camera);

        // center the image at 0,0
        DrawTexture(ImageTexture, ImageTexture.width / -2, ImageTexture.height / -2, WHITE);

        EndMode2D();
        EndTextureMode();
    }

    void Shutdown() override {
        UnloadRenderTexture(ViewTexture);
        UnloadTexture(ImageTexture);
    }
};

class SceneViewWindow : public DocumentWindow {
   public:
    Camera3D Camera = {0};

    void Setup() override {
        ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

        Camera.fovy = 45;
        Camera.up.y = 1;
        Camera.position.y = 3;
        Camera.position.z = -25;

        Image img = GenImageChecked(ScaleToDPII(256), ScaleToDPII(256), ScaleToDPII(32), ScaleToDPII(32), DARKGRAY, WHITE);
        GridTexture = LoadTextureFromImage(img);
        UnloadImage(img);
        GenTextureMipmaps(&GridTexture);
        SetTextureFilter(GridTexture, TEXTURE_FILTER_ANISOTROPIC_16X);
        SetTextureWrap(GridTexture, TEXTURE_WRAP_CLAMP);
    }

    void Shutdown() override {
        UnloadRenderTexture(ViewTexture);
        UnloadTexture(GridTexture);
    }

    void Show() override {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::SetNextWindowSizeConstraints(ImVec2(ScaleToDPIF(400.0f), ScaleToDPIF(400.0f)), ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));

        if (ImGui::Begin("3D View", &Open, ImGuiWindowFlags_NoScrollbar)) {
            Focused = ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows);
            // draw the view
            rlImGuiImageRenderTextureFit(&ViewTexture, true);
        }
        ImGui::End();
        ImGui::PopStyleVar();
    }

    void Update() override {
        ZoneScopedN("Scene View Update()");

        if (!Open)
            return;

        if (IsWindowResized()) {
            UnloadRenderTexture(ViewTexture);
            ViewTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
        }

        float period = 10;
        float magnitude = 25;

        Camera.position.x = sinf(float(GetTime() / period)) * magnitude;

        BeginTextureMode(ViewTexture);
        ClearBackground(SKYBLUE);

        BeginMode3D(Camera);

        // grid of cube trees on a plane to make a "world"
        DrawPlane(Vector3{0, 0, 0}, Vector2{50, 50}, BEIGE);  // simple world plane
        float spacing = 4;
        int count = 5;

        for (float x = -count * spacing; x <= count * spacing; x += spacing) {
            for (float z = -count * spacing; z <= count * spacing; z += spacing) {
                Vector3 pos = {x, 0.5f, z};

                Vector3 min = {x - 0.5f, 0, z - 0.5f};
                Vector3 max = {x + 0.5f, 1, z + 0.5f};

                DrawCube(Vector3{x, 1.5f, z}, 1, 1, 1, GREEN);
                DrawCube(Vector3{x, 0.5f, z}, 0.25f, 1, 0.25f, BROWN);
            }
        }

        EndMode3D();
        EndTextureMode();
    }

    Texture2D GridTexture = {0};
};

PlaygroundViewerWindow playgroundViewer;
SceneViewWindow sceneView;

void DoMainMenu() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Exit"))
                Quit = true;

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window")) {
            ImGui::MenuItem("ImGui Demo", nullptr, &ImGuiDemoOpen);
            ImGui::MenuItem("Image Viewer", nullptr, &playgroundViewer.Open);
            ImGui::MenuItem("3D View", nullptr, &sceneView.Open);

            ImGui::EndMenu();
        }
    }
    ImGui::EndMainMenuBar();
}

void s3d::Editor::StartClientWithEditor() {
    rlImGuiSetup(true);
    s3d::Editor::SetEditorThemeToDefault();
    ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    playgroundViewer.Setup();
    playgroundViewer.Open = true;

    sceneView.Setup();
    sceneView.Open = true;

    // Main game loop
    while (!WindowShouldClose() && !Quit)  // Detect window close button or ESC key
    {
        playgroundViewer.Update();
        sceneView.Update();

        BeginDrawing();
        ClearBackground(DARKGRAY);

        rlImGuiBegin();
        ImGui::DockSpaceOverViewport(0, NULL, ImGuiDockNodeFlags_PassthruCentralNode);
        DoMainMenu();

        if (ImGuiDemoOpen)
            ImGui::ShowDemoWindow(&ImGuiDemoOpen);
        ImGui::ShowMetricsWindow();

        if (playgroundViewer.Open)
            playgroundViewer.Show();

        if (sceneView.Open)
            sceneView.Show();

        rlImGuiEnd();

        EndDrawing();
        //----------------------------------------------------------------------------------
        FrameMark;
    }
    rlImGuiShutdown();

    playgroundViewer.Shutdown();
    sceneView.Shutdown();
}