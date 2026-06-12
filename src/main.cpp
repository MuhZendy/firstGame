#include <iostream>
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Resizable Window Example");
    
    rlImGuiSetup(true);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        rlImGuiBegin();

        DrawRectangle(150, 150, 200, 150, Color{ 0, 121, 241, 127 });
        DrawRectangle(100, 100, 200, 150, Color{ 230, 41, 55, 127 });

        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("This is a resizable window example using raylib and ImGui.");
        ImGui::End();

        rlImGuiEnd();

        EndDrawing();
    }
    
    rlImGuiShutdown();

    CloseWindow();

    return 0;
}