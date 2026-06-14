#include <iostream>

#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

#include "gameMain.h"

void imGuiWindow() {
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize;
    ImGui::Begin("Second Window", nullptr, windowFlags);
    static char buffer[128] = "";
    ImGuiInputTextFlags flags =
        ImGuiInputTextFlags_CharsNoBlank |        // no spaces
        ImGuiInputTextFlags_EnterReturnsTrue |    // return true on Enter
        ImGuiInputTextFlags_AutoSelectAll;        // select all text when focused
    
    if (ImGui::InputText("Player Name", buffer, sizeof(buffer), flags))
    {
        std::cout << "Confirmed name: " << buffer << "\n";
    }
    ImGui::End();
}

int main() {

#if PRODUCTION_BUILD == 1
    SetTraceLogLevel(LOG_ERROR); // Only log errors in production builds
#endif

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Resizable Window Example");
    SetExitKey(0); // Disable default exit key (ESC)
    SetTargetFPS(60);

    rlImGuiSetup(true);

#pragma region ImGui Configuration
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
    io.FontGlobalScale = 2.0f; // Scale ImGui fonts for better visibility
#pragma endregion

    if (!initGame()) {
        std::cerr << "Failed to initialize game.\n";
        return -1;
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        
        rlImGuiBegin();
        ImGui::PushStyleColor(ImGuiCol_WindowBg, {}); // Make the main window background transparent
        ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {}); // Make the docking background transparent
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
        ImGui::PopStyleColor(2); // Pop the two colors we pushed

        if (!updateGame()) {
            CloseWindow();
        }

        rlImGuiEnd();

        EndDrawing();
    }
    
    rlImGuiShutdown();

    CloseWindow();
    std::cout << "Game requested to close.\n";

    return 0;
}