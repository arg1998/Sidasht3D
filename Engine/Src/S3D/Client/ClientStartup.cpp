#include "Client.hpp"
#include "S3D/Profiler/Profiler.hpp"

#include <raylib.h>

void s3d::Client::StartClient() {

     // Main game loop
     while (!WindowShouldClose())  // Detect window close button or ESC key
     {
 
         BeginDrawing();
         ClearBackground(DARKGRAY);
 
         EndDrawing();
         //----------------------------------------------------------------------------------
         FrameMark;
     }
    
}