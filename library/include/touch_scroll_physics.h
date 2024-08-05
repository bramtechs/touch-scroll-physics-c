#ifndef H_TOUCH_SCROLL_PHYSICS
#define H_TOUCH_SCROLL_PHYSICS

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>    
#endif

#define INPUT_DELTA_MAX_HISTORY 3
    
typedef struct TouchScroller
{
    // --- configuration ---
    int totalCells;
    float viewSize;
    float cellSize;
    float gutterSize;
    bool dipToClosestCell;
    float dipMaxSpeed;             // recommended: 10.f
    float dipSnappiness;           // recommended: 0.1f
    // ---------------------

    // --- result ---
    float offset;
    // --------------
    
    // private
    float momentum;
    float lastInput;
    bool interacting;
    float inputDelta;
    int inputDeltaIndex;
    float inputDeltas[INPUT_DELTA_MAX_HISTORY];
    float delta;
} TouchScroller;

void TouchScroller_Update(TouchScroller*, float dtInMillis);

void TouchScroller_Start(TouchScroller*, float offset);
void TouchScroller_Move(TouchScroller*, float offset);
void TouchScroller_End(TouchScroller*, float offset);
bool TouchScroller_IsVisible(TouchScroller*, float startOffset, float endOffset);

float TouchScroller_GetOffset(TouchScroller*);
#define TouchScroller_GetValue(X) TouchScroller_GetOffset(X)

#ifdef __cplusplus
}
#endif

#endif
