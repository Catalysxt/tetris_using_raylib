// Implements the state stack operations.

#include "state_manager.h"

void StateManager::PushState(std::unique_ptr<GameState> state)
{
    // std::move transfers ownership of the state into the vector.
    // Unique_ptr enforces "one owner" rule

    m_states.push_back(std::move(state));
    m_states.back()->OnEnter();
}

void StateManager::PopState()
{
    if (!m_states.empty())
    {
        m_states.back()->OnExit();

        // pop_back() destroys the unique_ptr, which automatically
        // calls 'delete' on the GameState it owns. No manual cleanup.
        m_states.pop_back();
    }
}

void StateManager::SwapState(std::unique_ptr<GameState> state)
{
    // Remove the current top state, then push the new one.
    // We do this as two separate operations to keep the logic simple
    // and reuse the OnExit/OnEnter lifecycle calls.
    PopState();
    PushState(std::move(state));
}

void StateManager::HandleInput(const InputHandler& input)
{
    if (!m_states.empty()) { m_states.back()->HandleInput(input); }
}

void StateManager::Update(double dt, AudioHandler& audio)
{
    if (!m_states.empty()) { m_states.back()->Update(dt, audio); }
}

void StateManager::Render(const Renderer& renderer) const
{
    if (!m_states.empty()) { m_states.back()->Render(renderer); }
}

bool StateManager::IsEmpty() const
{
    return m_states.empty();
}
