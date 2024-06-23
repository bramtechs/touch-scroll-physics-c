#pragma once

#include "touch_scroll_physics.h"

class CTouchScroller
{
public:
    CTouchScroller(TouchScrollerConfig config);
    virtual ~CTouchScroller();

    CTouchScroller(const CTouchScroller&) = delete;

    void Start(float xOrY);
    void Move(float xOrY);
    void End(float xOrY);
    
    void Update(float dt = 0.f);
    
    float GetValue() const;
private:
    TouchScroller* m_scroller;
};

class CTouchScrollerRaylib : public CTouchScroller
{
public:
    CTouchScrollerRaylib(TouchScrollerConfig config);
    float ProcessX(int mButton);
};
