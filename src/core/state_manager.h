// state_manager.h
//
// Manages a stack of game states using std::unique_ptr for ownership.
//
// Why a vector instead of std::stack?
// std::stack only lets you access the top element. But sometimes we need
// to render *all* states in the stack (e.g., drawing the game board
// behind a semi-transparent pause overlay). A vector gives us that
// flexibility while still functioning as a stack via push_back/pop_back.
//
// Why unique_ptr?
// Each state is dynamically allocated (because we don't know the concrete
// type at compile time — it could be PlayState, MenuState, etc.).
// unique_ptr ensures exactly ONE owner and automatic deletion when the
// state is removed from the vector. No manual 'delete' needed.

#pragma once

#include "game_state.h"
#include "audio_handler.h"
#include <vector>
#include <memory>

class StateManager
{
public:
    // Adds a new state on top of the stack and calls its OnEnter().
    // Uses std::unique_ptr to enforce that the StateManager takes
    // full ownership — the caller gives up the pointer.
    void PushState(std::unique_ptr<GameState> state);

    // Removes the top state, calling OnExit() before destruction.
    // The unique_ptr automatically deletes the state object.
    void PopState();

    // Replaces the top state: pops the current one and pushes a new one.
    // Useful for transitions like "Playing → Game Over" where you don't
    // want the old state lingering underneath.
    void SwapState(std::unique_ptr<GameState> state);

    // These delegate to the top state on the stack.
    // If the stack is empty, they safely do nothing.
    void HandleInput(const InputHandler& input);
    void Update(double dt, AudioHandler& audio);
    void Render(const Renderer& renderer) const;

    // Returns true if there are no states on the stack.
    // Application can use this to know when to quit.
    [[nodiscard]] bool IsEmpty() const;

private:
    // The "stack" of states. Back of the vector = top of the stack.
    // Each element is a unique_ptr, so removing it automatically frees memory.
    std::vector<std::unique_ptr<GameState>> m_states;
};
