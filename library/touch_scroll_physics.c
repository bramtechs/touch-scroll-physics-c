#include <stdlib.h>
#include <math.h>

#include "touch_scroll_physics.h"

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

void TouchScroller_Update(TouchScroller* ts, float dt)
{
    // precalculate some values
    float fullSize = (float)fmax(ts->viewSize, ts->cellSize * ts->totalCells);
    float max = fullSize - ts->viewSize;
    float cellSizeHalf = ts->cellSize * 0.5f;
    float maxGutter = max + ts->gutterSize;

    bool isBefore = ts->offset < 0;
    bool isAfter = ts->offset > max;
    bool isInside = !isBefore && !isAfter;

    // ease input at edges
    if(isBefore) {
        ts->momentum = 0;
        if (ts->inputDelta > 0) {
            ts->inputDelta *= 1-(ts->offset / -ts->gutterSize);
        }
    } else if(isAfter) {
        ts->momentum = 0;
        if (ts->inputDelta < 0) {
            ts->inputDelta *= (maxGutter - ts->offset) / ts->gutterSize;
        }
    }

    ts->offset -= cellSizeHalf;
    float dip = 0;
    if (!ts->interacting) {
        if (isInside && ts->dipToClosestCell) {
            dip = (float)(fmod((fmod(ts->offset, ts->cellSize) + ts->cellSize), ts->cellSize)) - cellSizeHalf;
        } else if(isBefore) {
            dip = ts->offset + cellSizeHalf;
        } else if(isAfter) {
            dip = ts->offset - max + cellSizeHalf;
        }
        float dipStrength = (1.f-Clamp((float)(fabs(ts->momentum)) / ts->dipMaxSpeed, 0.f, 1.f)) * ts->dipSnappiness;
        dip *= dipStrength;
    }
    
    ts->offset -= ts->inputDelta;
    ts->inputDelta = 0;
    ts->offset -= ts->momentum;
    ts->momentum *= 0.9f;
    ts->offset -= dip;
    
    ts->offset += cellSizeHalf;
    ts->offset = Clamp(ts->offset, -ts->gutterSize, maxGutter);
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
        ts->inputDeltaIndex = (ts->inputDeltaIndex+1) % INPUT_DELTA_MAX_HISTORY;
        ts->inputDeltas[ts->inputDeltaIndex] = ts->inputDelta;
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

bool TouchScroller_IsVisible(TouchScroller* ts, float startOffset, float endOffset)
{
    if (startOffset > endOffset) {
        float temp = startOffset;
        startOffset = endOffset;
        endOffset = temp;
    }

    float viewStart = ts->offset;
    float viewEnd = ts->offset + ts->viewSize;

    if (startOffset < viewEnd && startOffset > viewStart) {
        return true;
    }
    if (endOffset < viewEnd && endOffset > viewStart) {
        return true;
    }

    return false;
}

float TouchScroller_GetOffset(TouchScroller* ts)
{
    return ts->offset;
}
