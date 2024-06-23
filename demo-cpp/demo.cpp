#include "raylib.h"
#include "raymath.h"

#include "touch_scroll_physics_wrapper.hpp"

int main()
{
    const int WIDTH = 800;
    const int HEIGHT = 600;
    
    InitWindow(WIDTH, HEIGHT, "Touch Scroll Physics - Demo C++");
    SetTargetFPS(60);

    Camera2D camera = {
        .offset = {0.f, 0.f},
        .target = {0.f, 0.f},
        .rotation = 0.f,
        .zoom = 1.f,
    };

    TouchScrollerConfig config = {
        .totalCells = 25,
        .viewSize = WIDTH,
        .cellSize = HEIGHT/4,
        .gutterSize = WIDTH/2,
        .dipToClosestCell = true
    };

    CTouchScrollerRaylib scroller(config);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(GetColor(0x3b3b3b));

            camera.target.x = scroller.ProcessX(MOUSE_BUTTON_LEFT);
            BeginMode2D(camera);
            {
                // Draw each cell
                for (int i = 0; i < config.totalCells; i++) {
                    float cellWidth = config.cellSize;
                    float cellHeight = HEIGHT;

                    Color cellColor = (i % 2 == 0) ? GetColor(0x7bb3d6) : GetColor(0xcfcfcf);
                    DrawRectangle(i*cellWidth, 0, cellWidth, cellHeight, cellColor);
                }
            }
            EndMode2D();
        }
        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}
