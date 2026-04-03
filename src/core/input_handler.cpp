// input_handler.cpp

#include "input_handler.h"

bool InputHandler::IsMoveLeftRequested() const
{
    // For movement, we use IsKeyDown so the user can hold the button.
    // In a professional Tetris game, we would implement "DAS" 
    // (Delayed Auto Shift) here, but for now, simple repeats work.
    return ::IsKeyPressed(KEY_LEFT) || ::IsKeyDown(KEY_LEFT);
}

bool InputHandler::IsMoveRightRequested() const
{
    return ::IsKeyPressed(KEY_RIGHT) || ::IsKeyDown(KEY_RIGHT);
}

bool InputHandler::IsForcedDropRequested() const
{
    return ::IsKeyDown(KEY_DOWN);
}

bool InputHandler::IsRotateCWRequested() const
{
    // For rotation, we only want a SINGLE action per press.
    // If we used IsKeyDown, the piece would spin like a fan!
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
