#include "touch_scroll_physics_wrapper.hpp"

CTouchScroller::CTouchScroller(TouchScrollerConfig config)
    : m_scroller(TouchScroller_Init(config))
{
}

CTouchScroller::~CTouchScroller()
{
    TouchScroller_Destroy(m_scroller);
}

void CTouchScroller::Start(float xOrY)
{
    TouchScroller_Start(m_scroller, xOrY);
}

void CTouchScroller::Move(float xOrY)
{
    TouchScroller_Move(m_scroller, xOrY);
}

void CTouchScroller::End(float xOrY)
{
    TouchScroller_End(m_scroller, xOrY);
}

void CTouchScroller::Update(float dt)
{
    TouchScroller_Update(m_scroller, dt);
}

float CTouchScroller::GetValue() const
{
    return TouchScroller_GetValue(m_scroller);
}

// raylib specific

#include "raylib.h"

CTouchScrollerRaylib::CTouchScrollerRaylib(TouchScrollerConfig config)
    : CTouchScroller(config)
{
}

float CTouchScrollerRaylib::ProcessX(int mButton)
{
    if (IsMouseButtonPressed(mButton)) {
        Start(GetMouseX());
    }
    else if (IsMouseButtonReleased(mButton)) {
        End(GetMouseX());
    }
    else if (IsMouseButtonDown(mButton)) {
        Move(GetMouseX());
    }
    
    Update(GetFrameTime() * 1000.f);
    return GetValue();
}
