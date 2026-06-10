#include <iostream>
#include "raylib.h"

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 600, "Resizable Window Example");
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawRectangle(150, 150, 200, 150, Color{ 0, 121, 241, 127 });
        DrawRectangle(100, 100, 200, 150, Color{ 230, 41, 55, 127 });

        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}