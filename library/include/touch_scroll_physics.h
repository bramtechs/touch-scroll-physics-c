#ifndef H_TOUCH_SCROLL_PHYSICS
#define H_TOUCH_SCROLL_PHYSICS

#ifdef __cplusplus
extern "C" {
#endif

struct TouchScrollerConfig;
struct TouchScroller;

#ifdef TSCROLL_USE_TYPEDEFS
typedef struct TouchScrollerConfig TouchScrollerConfig;
typedef struct TouchScroller TouchScroller;
#endif

#include <stdbool.h>

struct TouchScrollerConfig
{
    int totalCells;
    float viewSize;
    float cellSize;
    float gutterSize;
    bool dipToClosestCell;
};

struct TouchScroller* TouchScroller_Init(const struct TouchScrollerConfig);
void TouchScroller_Destroy(struct TouchScroller*);

void TouchScroller_Update(struct TouchScroller*, float dtInMillis);

void TouchScroller_Start(struct TouchScroller*, float xOrYPos);
void TouchScroller_Move(struct TouchScroller*, float xOrYPos);
void TouchScroller_End(struct TouchScroller*, float xOrYPos);

float TouchScroller_GetValue(struct TouchScroller*);

#endif

#ifdef __cplusplus
}
#endif
