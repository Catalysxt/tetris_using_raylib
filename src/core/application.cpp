// Implements the Application lifecycle and the fixed-timestep game loop.
//
// All Update/Render calls are delegated to whatever
// state is on top of the stack .

#include "application.h"
#include "../states/play_state.h"
#include <raylib.h>

Application::Application(const WindowConfig& config)
{
    InitWindow(config.width, config.height, config.title);
    SetTargetFPS(config.targetFps);

    // Create the state manager and push the initial gameplay state.
    // Application has no idea what play state is active, either menu or game over screen. It doesn't need to.
    m_stateManager = std::make_unique<StateManager>();
    m_stateManager->PushState(std::make_unique<PlayState>(m_stateManager.get()));
}

Application::~Application()
{
    // Cleanup tasks
    CloseWindow();
}

void Application::Run()
{
    // The main loop runs until the user closes the window or all
    // states have been popped (nothing left to do).
    while (!WindowShouldClose() && m_isRunning && !m_stateManager->IsEmpty())
    {
        // Step 1: Measure how much real time passed since the last frame
        // and add it to the accumulator inside GameClock.
        clock_.Tick();

        // Step 2: Let the current state process input before any updates.
        // This happens once per frame (not per fixed tick) because input
        // events are inherently tied to real-time user actions.
        m_stateManager->HandleInput(m_input);

        // Step 3: Consume accumulated time in fixed-size steps.
        //
        // Why a while-loop instead of a single if?
        // If the frame took longer than one timestep (e.g., the OS had a
        // hiccup), we might need multiple logic updates to catch up. This
        // ensures game logic always runs at the same effective speed regardless
        // of rendering performance — crucial for deterministic behavior.
        while (clock_.ShouldUpdate())
        {
            Update(TimeConfig::FIXED_TIMESTEP, m_audio);
        }

        // Step 4: Render the current state.
        Render(clock_.GetInterpolationAlpha());
    }
}

void Application::Update(double dt, AudioHandler& audio)
{
    // Delegate all game logic to the current state.
    // The StateManager forwards this to whatever state is on top of
    // the stack (PlayState, MenuState, etc.)
    m_stateManager->Update(dt, audio);
}

void Application::Render(double interpolationAlpha)
{
    // Delegate all rendering to the current state, but wrap it
    // in our abstract Renderer's frame lifecycle.
    (void)interpolationAlpha;
    
    m_renderer.BeginFrame();
    m_stateManager->Render(m_renderer);
    m_renderer.EndFrame();
}
