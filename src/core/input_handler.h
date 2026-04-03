// Encapsulates keyboard and controller handling.

// - The Proxy Pattern:
//   Instead of calling `IsKeyPressed(KEY_LEFT)` inside PlayState,
//   we call `input.IsMoveLeftRequested()`.
//
// - Decoupling Inputs from Actions:
//   If we ever want to add controller support or let the player
//   rebind keys (e.g., use 'A' instead of Left Arrow), we only
//   change the code in this one file. The rest of the game
//   logic stays exactly the same.

#pragma once

#include <raylib.h>

class InputHandler
{
public:
    // We don't need a constructor for now, but we'll use a const
    // interface to ensure our state methods don't modify the handler.
    InputHandler() = default;

    // Updates internal timers for DAS (Delayed Auto Shift).
    // Called once per frame in the main loop.
    void Update();

    // Returns true if the user just pressed the Left move key.
    [[nodiscard]] bool IsMoveLeftRequested() const;

    // Returns true if the user just pressed the Right move key.
    [[nodiscard]] bool IsMoveRightRequested() const;

    // Returns true if the user wants to drop the piece faster.
    [[nodiscard]] bool IsForcedDropRequested() const;

    // Returns true for a single press of the rotation keys.
    [[nodiscard]] bool IsRotateCWRequested() const;
    [[nodiscard]] bool IsRotateCCWRequested() const;

    // Returns true for an instant drop to the bottom.
    [[nodiscard]] bool IsHardDropRequested() const;

    // Returns true if the user wants to pause or exit back.
    [[nodiscard]] bool IsQuitRequested() const;

private:
    // Tracks how long movement keys have been held down
    double m_leftHoldTime = 0.0;
    double m_rightHoldTime = 0.0;
    
    // Cached results calculated during Update()
    bool m_moveLeftReady = false;
    bool m_moveRightReady = false;

    // Delayed Auto Shift (DAS): How long to hold before repeating (e.g., 170ms)
    // Auto Repeat Rate (ARR): Time between repeats once DAS kicks in (e.g., 50ms)
    static constexpr double DAS_DELAY = 0.17;
    static constexpr double ARR_RATE = 0.05;
};
