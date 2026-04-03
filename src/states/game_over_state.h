// game_over_state.h
//
// Displayed when the player Tops Out. Waits for input to restart.

#pragma once

#include "../core/game_state.h"
#include "../core/state_manager.h"
#include <raylib.h>

class AudioHandler;

class GameOverState : public GameState
{
public:
    explicit GameOverState(StateManager* stateManager, AudioHandler* audio);

    void OnEnter() override;
    void OnExit() override;
    void HandleInput(const InputHandler& input) override;
    void Update(double dt, AudioHandler& audio) override;
    void Render(const Renderer& renderer) const override;

private:
    StateManager* m_stateManager;
    AudioHandler* m_audio;
};
