#pragma once

// The State pattern:

// Forward declarations
class Renderer;
class InputHandler;
class AudioHandler;

// GameState is an ABC for each game state. Each method is intended to be overidden by
// GameStates such as Main Menu, Gameplay, Pause, Game Over etc. 

class GameState
{
public:
    // Virtual destructor ensures proper cleanup when deleting through
    // a GameState pointer
    virtual ~GameState() = default;

    // Called once when this state becomes active (pushed onto the stack).
    // Use it for initialization that shouldn't happen in the constructor
    // (e.g., resetting scores, spawning the first piece).
    virtual void OnEnter() = 0;

    // Called once when this state is removed from the stack.
    // Use it for cleanup that shouldn't wait for the destructor
    // (e.g., saving progress, stopping music).
    virtual void OnExit() = 0;

    // Reads input and translates it into actions for this state.
    // Distinct from Update()
    virtual void HandleInput(const InputHandler& input) = 0;

    // Advances game logic by one fixed timestep.
    virtual void Update(double dt, AudioHandler& audio) = 0;

    // Draws the current state to the screen.
    // 'const Renderer&' means the state can ask the Renderer to draw things,
    // but cannot modify the Renderer itself.
    // The trailing 'const' means rendering cannot modify the game state either.
    virtual void Render(const Renderer& renderer) const = 0;
};
