// input_handler.cpp

#include "input_handler.h"

void InputHandler::Update()
{
    // GetFrameTime() returns the time in seconds since the last frame.
    // This connects our input to real-world time ticking instead of frames.
    double dt = ::GetFrameTime();

    // ===============================================================
    // LEFT MOVEMENT (DAS + ARR Logic)
    // ===============================================================
    m_moveLeftReady = false;
    if (::IsKeyDown(KEY_LEFT)) 
    {
        if (::IsKeyPressed(KEY_LEFT)) 
        {
            m_moveLeftReady = true; // Instant initial movement
        }
        else
        {
            double oldTime = m_leftHoldTime;
            m_leftHoldTime += dt;
            
            if (m_leftHoldTime >= DAS_DELAY)
            {
                // Calculate how many ARR "ticks" happened before and after this frame
                double priorOverflow = (oldTime < DAS_DELAY) ? 0.0 : (oldTime - DAS_DELAY);
                double currentOverflow = m_leftHoldTime - DAS_DELAY;
                
                int priorRepeats = static_cast<int>(priorOverflow / ARR_RATE);
                int currentRepeats = static_cast<int>(currentOverflow / ARR_RATE);
                
                // If the number of repeats increased this frame, we trigger a move!
                if (currentRepeats > priorRepeats)
                {
                    m_moveLeftReady = true;
                }
            }
        }
    }
    else 
    {
        m_leftHoldTime = 0.0;
    }

    // ===============================================================
    // RIGHT MOVEMENT (DAS + ARR Logic)
    // ===============================================================
    m_moveRightReady = false;
    if (::IsKeyDown(KEY_RIGHT)) 
    {
        if (::IsKeyPressed(KEY_RIGHT)) 
        {
            m_moveRightReady = true; // Instant initial movement
        }
        else
        {
            double oldTime = m_rightHoldTime;
            m_rightHoldTime += dt;
            
            if (m_rightHoldTime >= DAS_DELAY)
            {
                double priorOverflow = (oldTime < DAS_DELAY) ? 0.0 : (oldTime - DAS_DELAY);
                double currentOverflow = m_rightHoldTime - DAS_DELAY;
                
                int priorRepeats = static_cast<int>(priorOverflow / ARR_RATE);
                int currentRepeats = static_cast<int>(currentOverflow / ARR_RATE);
                
                if (currentRepeats > priorRepeats)
                {
                    m_moveRightReady = true;
                }
            }
        }
    }
    else 
    {
        m_rightHoldTime = 0.0;
    }
}

bool InputHandler::IsMoveLeftRequested() const
{
    return m_moveLeftReady;
}

bool InputHandler::IsMoveRightRequested() const
{
    return m_moveRightReady;
}

bool InputHandler::IsForcedDropRequested() const
{
    return ::IsKeyDown(KEY_DOWN);
}

bool InputHandler::IsRotateCWRequested() const
{
    return ::IsKeyPressed(KEY_UP) || ::IsKeyPressed(KEY_X);
}

bool InputHandler::IsRotateCCWRequested() const
{
    return ::IsKeyPressed(KEY_Z);
}

bool InputHandler::IsHardDropRequested() const
{
    return ::IsKeyPressed(KEY_SPACE);
}

bool InputHandler::IsQuitRequested() const
{
    return ::IsKeyPressed(KEY_ESCAPE);
}
