#include <stdlib.h>
#include <math.h>

#include "touch_scroll_physics.h"

#define INPUT_DELTA_MAX_HISTORY 3

struct TouchScroller
{
    int totalCells;
    float viewSize;
    float cellSize;
    float gutterSize;
    bool dipToClosestCell;
    
    float value;
    float momentum;

    float lastInput;
    bool interacting;
    
    float inputDelta;
    int inputDeltaIndex;
    float inputDeltas[INPUT_DELTA_MAX_HISTORY];

    // private
    float fullSize;
    float dipMaxSpeed;
    float dipSnappiness;
    float cellSizeHalf;
    float max;
    float maxGutter;
    float delta;
};

static void UpdateSize(struct TouchScroller* ts)
{
    ts->cellSizeHalf = ts->cellSize * 0.5;
    ts->fullSize = fmax(ts->viewSize, ts->cellSize * ts->totalCells);
    ts->max = ts->fullSize - ts->viewSize;
    ts->maxGutter = ts->max + ts->gutterSize;
}

static float Clamp(float a, float min, float max)
{
    if (a < min) {
        return min;
    }
    if (a > max) {
        return max;
    }
    return a;
}

struct TouchScroller* TouchScroller_Init(const struct TouchScrollerConfig opt)
{
    struct TouchScroller* ts = calloc(1, sizeof(struct TouchScroller));
    if (ts) {
        ts->totalCells = opt.totalCells;
        ts->viewSize = opt.viewSize;
        ts->cellSize = opt.cellSize;
        ts->gutterSize = opt.gutterSize;
        ts->dipToClosestCell = opt.dipToClosestCell;
        ts->dipMaxSpeed = 10;
        ts->dipSnappiness = 0.1f;
        UpdateSize(ts);
    }
    return ts;
}

void TouchScroller_Destroy(struct TouchScroller* ts)
{
    if (ts) {
        free(ts);
    }
}

void TouchScroller_Update(struct TouchScroller* ts, float dt)
{
    bool isBefore = ts->value < 0;
    bool isAfter = ts->value > ts->max;
    bool isInside = !isBefore && !isAfter;

    // ease input at edges
    if(isBefore) {
        ts->momentum = 0;
        if (ts->inputDelta > 0) {
            ts->inputDelta *= 1-(ts->value / -ts->gutterSize);
        }
    } else if(isAfter) {
        ts->momentum = 0;
        if (ts->inputDelta < 0) {
            ts->inputDelta *= (ts->maxGutter - ts->value) / ts->gutterSize;
        }
    }

    bool dipping = !ts->interacting;
    
    ts->value -= ts->cellSizeHalf;
    float dip = 0;
    if (dipping) {
        if (isInside && ts->dipToClosestCell) {
            dip = fmod((fmod(ts->value, ts->cellSize) + ts->cellSize), ts->cellSize) - ts->cellSizeHalf; 
        } else if(isBefore) {
            dip = ts->value + ts->cellSizeHalf;
        } else if(isAfter) {
            dip = ts->value - ts->max + ts->cellSizeHalf;
        }
        float dipStrength = (1.f-Clamp(fabs(ts->momentum) / ts->dipMaxSpeed, 0.f, 1.f)) * ts->dipSnappiness;
        dip *= dipStrength;
    }
    
    ts->value -= ts->inputDelta;
    ts->inputDelta = 0;
    ts->value -= ts->momentum;
    ts->momentum *= 0.9;
    ts->value -= dip;
    
    ts->value += ts->cellSizeHalf;
    ts->value = Clamp(ts->value, -ts->gutterSize, ts->maxGutter);
}

void TouchScroller_Start(struct TouchScroller* ts, float value)
{
    ts->interacting = true;
    ts->momentum = 0;
    ts->inputDelta = 0;
    ts->lastInput = value;
}

void TouchScroller_Move(struct TouchScroller* ts, float value)
{
    if (ts->interacting) {
        ts->inputDelta = value - ts->lastInput;
        ts->inputDeltas[ts->inputDeltaIndex] = ts->inputDelta;
        ts->inputDeltaIndex = (ts->inputDeltaIndex+1) % INPUT_DELTA_MAX_HISTORY;
        ts->lastInput = value;
    }
}

void TouchScroller_End(struct TouchScroller* ts, float value)
{   
    if (ts->interacting) {
        ts->interacting = false;

        ts->momentum = 0.f;
        for (int i = 0; i < INPUT_DELTA_MAX_HISTORY; i++) {
            if (ts->momentum < fabs(ts->inputDeltas[i])) {
                ts->momentum = ts->inputDeltas[i];
            }
        }
        
        ts->delta = 0;
        for (int i = 0; i < INPUT_DELTA_MAX_HISTORY; i++) {
            ts->inputDeltas[i] = 0;
        }
    }
}

float TouchScroller_GetValue(struct TouchScroller* ts)
{
    return ts->value;
}
