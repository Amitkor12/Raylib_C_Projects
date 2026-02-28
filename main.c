#include "raylib.h"

int main(void)
{
    int window_width = 800;
    int window_height = 450;
    InitWindow(window_width, window_height, "Raylib C Example");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        DrawText("Hello Raylib + C + Linux!", 250, 200, 25, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
