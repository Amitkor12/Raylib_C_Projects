#include "raylib.h"
#include "AnalogClock.h"

int main(void)
{
    int window_width = 600;
    int window_height = 600;
    InitWindow(window_width, window_height, "Raylib C Example");
    SetTargetFPS(60);

    s_AnalogClockData analogClock;
    AnalogClock_Init(&analogClock,250,(Vector2){300,300});

    while (!WindowShouldClose()) {
        Update(&analogClock);
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        Draw(&analogClock);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
