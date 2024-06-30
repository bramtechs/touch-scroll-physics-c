#include "raylib.h"
#include "raymath.h"

#define TSCROLL_USE_TYPEDEFS
#include "touch_scroll_physics.h"

static float ProcessTouchScrollerX(TouchScroller* scroller, int mButton)
{
    if (IsMouseButtonPressed(mButton)) {
        TouchScroller_Start(scroller, (float)GetMouseX());
    }
    else if (IsMouseButtonReleased(mButton)) {
        TouchScroller_End(scroller, (float)GetMouseX());
    }
    else if (IsMouseButtonDown(mButton)) {
        TouchScroller_Move(scroller, (float)GetMouseX());
    }
    
    float dt = GetFrameTime() * 1000.f;
    TouchScroller_Update(scroller, dt);
    return TouchScroller_GetValue(scroller);
}

int main(void)
{
    const int WIDTH = 800;
    const int HEIGHT = 600;
    
    InitWindow(WIDTH, HEIGHT, "Touch Scroll Physics - Demo C");
    SetTargetFPS(60);

    Camera2D camera = {
        .offset = {0.f, 0.f},
        .target = {0.f, 0.f},
        .rotation = 0.f,
        .zoom = 1.f,
    };

    TouchScroller scroller = {
        .totalCells = 25,
        .viewSize = (float)WIDTH,
        .cellSize = HEIGHT/4.f,
        .gutterSize = WIDTH/2.f,
        .dipToClosestCell = true,
        .dipMaxSpeed = 10.f,
        .dipSnappiness = 0.1f
    };

    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(GetColor(0x3b3b3b));

            camera.target.x = ProcessTouchScrollerX(&scroller, MOUSE_BUTTON_LEFT);
            BeginMode2D(camera);
            {
                // Draw each cell
                for (int i = 0; i < scroller.totalCells; i++) {
                    float cellWidth = scroller.cellSize;
                    float cellHeight = (float)HEIGHT;

                    Color cellColor = (i % 2 == 0) ? GetColor(0x7bb3d6ff) : GetColor(0xcfcfcfff);
                    DrawRectangleRec((Rectangle){i*cellWidth, 0.f, cellWidth, cellHeight}, cellColor);
                }
            }
            EndMode2D();
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
