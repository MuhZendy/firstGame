#include <iostream>
#include "raylib.h"
#include "imgui.h"
#include "rlImGui.h"

void imGuiWindow2() {
    ImGui::Begin("Second Window");
    ImGui::Text("This is the second window.");
    ImGui::Separator();
    ImGui::NewLine();
    static float sliderValue = 0.0f;
    ImGui::SliderFloat("Slider", &sliderValue, 0.0f, 100.0f);
    ImGui::End();
}

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Resizable Window Example");
    
    rlImGuiSetup(true);

#pragma region ImGui Configuration
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
    io.FontGlobalScale = 2.0f; // Scale ImGui fonts for better visibility
#pragma endregion

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        rlImGuiBegin();
        ImGui::PushStyleColor(ImGuiCol_WindowBg, {}); // Make the main window background transparent
        ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {}); // Make the docking background transparent
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
        ImGui::PopStyleColor(2); // Pop the two colors we pushed

        DrawRectangle(150, 150, 200, 150, Color{ 0, 121, 241, 127 });
        DrawRectangle(100, 100, 200, 150, Color{ 230, 41, 55, 127 });

        ImGui::ShowDemoWindow();
        ImGui::Begin("Hello, ImGui!");
        ImGui::Text("This is a resizable window example using raylib and ImGui.");
        if (ImGui::Button("Click Me")) {
            std::cout << "Button Clicked!" << std::endl;
        }
        ImGui::End();

        imGuiWindow2();

        rlImGuiEnd();

        EndDrawing();
    }
    
    rlImGuiShutdown();

    CloseWindow();

    return 0;
}