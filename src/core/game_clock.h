// game_clock.h
// Provides a frame-rate-independent timing system for the game loop.
//
// Games need a consistent sense of time regardless of how fast the computer
// renders frames. If we tie game logic to frame rate, the game speeds up on
// fast machines and slows down on slow ones. GameClock tracks elapsed time
// and splits it into fixed-size "ticks" so the simulation always advances
// at the same rate — a technique borrowed from firmware real-time systems.

#pragma once

#include <raylib.h>

// We store all timing configuration in a single struct so it can be
// defined once at compile time and shared across the codebase.
// 'constexpr' means the compiler evaluates these values at compile time,
// so there's zero runtime cost — similar to #define but type-safe.
struct TimeConfig
{
    static constexpr double FIXED_TIMESTEP = 1.0 / 60.0;  // 60 updates per second
    static constexpr double MAX_FRAME_TIME = 0.25;         // Safety cap (explained below)
};

class GameClock
{
public:
    // No definition for constuctor. We'll rely on default constructor

    // Captures how much real time passed since the last frame.
    // We cap it to avoid a "spiral of death" — if the game freezes for a
    // moment (e.g., OS stall), the accumulated time could demand hundreds of
    // updates to catch up, which would freeze it even longer. Capping to
    // MAX_FRAME_TIME means we accept some slowdown instead of a crash.
    void Tick()
    {
        double frameTime = static_cast<double>(GetFrameTime());

        if (frameTime > TimeConfig::MAX_FRAME_TIME)
        {
            frameTime = TimeConfig::MAX_FRAME_TIME;
        }

        m_accumulator_ += frameTime;
    }

    // Returns true if there's enough accumulated time for another fixed update.
    // The game loop calls this repeatedly in a while-loop, consuming one
    // FIXED_TIMESTEP of accumulated time per iteration. This guarantees the
    // physics/logic runs at a constant rate even if rendering is faster or slower.
    [[nodiscard]] bool ShouldUpdate()
    {
        if (m_accumulator_ >= TimeConfig::FIXED_TIMESTEP)
        {
            m_accumulator_ -= TimeConfig::FIXED_TIMESTEP;
            return true;
        }
        return false;
    }

    // Returns a value between 0.0 and 1.0 representing how far we are between
    // the last fixed update and the next one. This can be used to interpolate
    // rendering positions for ultra-smooth visuals, but for Tetris (a grid game)
    // we won't need it much. It's here because it's the correct pattern.
    [[nodiscard]] double GetInterpolationAlpha() const
    {
        return m_accumulator_ / TimeConfig::FIXED_TIMESTEP;
    }

private:
    // Tracks leftover time that hasn't been consumed by fixed updates yet.
    // Think of it like a bucket that fills with real time each frame,
    // and drains in fixed-size chunks each update tick.
    double m_accumulator_ = 0.0;
};
