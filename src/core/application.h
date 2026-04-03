// application.h
// The top-level controller for the entire game.
//
// Application uses the RAII pattern (Resource Acquisition Is Initialization):
// the constructor opens the window and acquires resources, and the destructor
// releases them. This guarantees cleanup even if an exception is thrown

// Jurdisdiction is the main game loop.

#pragma once

#include "game_clock.h"
#include "input_handler.h"
#include "audio_handler.h"
#include "state_manager.h"
#include "../rendering/renderer.h"
#include <memory>
 
struct WindowConfig
{
    int width        = 800;
    int height       = 600;
    const char* title = "Tetris";
    int targetFps    = 60;
};

class Application
{
public:
    // Opens the Raylib window
    explicit Application(const WindowConfig& config = WindowConfig{});

    // Closes the Raylib window.
    ~Application();

    // We delete copy and move operations because having two Application
    // objects would mean two owners of the same Raylib window, which would
    // cause a double-close crash. Deleting these makes it a compile error
    // to accidentally duplicate the object.
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(Application&&) = delete;

    // The main entry point — call this once from main(). It runs the game loop. Everything happens inside here
    void Run();

private:
    // Called once per fixed timestep tick (e.g., 60 times per second).
    // All game logic — movement, collisions, scoring — goes here.
    // The 'dt' parameter is always FIXED_TIMESTEP, but we pass it explicitly
    // so the function signature documents its dependency on time.
    // Steps 1 through 4 inside the app loop.
    void Update(double dt, AudioHandler& audio);

    // Called once per frame (as fast as the monitor allows).
    // All drawing happens here. 'interpolationAlpha' could be used to
    // smooth between the last two Update positions, but for a grid-based
    // game like Tetris we just draw the current state.
    void Render(double interpolationAlpha);

    GameClock clock_;
    InputHandler m_input;
    AudioHandler m_audio;
    Renderer m_renderer;
    std::unique_ptr<StateManager> m_stateManager;
    bool m_isRunning = true;
};
