// game_over_state.cpp

#include "game_over_state.h"
#include "play_state.h"
#include "../core/input_handler.h"
#include "../rendering/renderer.h"

GameOverState::GameOverState(StateManager* stateManager)
    : m_stateManager(stateManager)
{
}

void GameOverState::OnEnter()
{
}

void GameOverState::OnExit()
{
}

void GameOverState::HandleInput(const InputHandler& input)
{
    // Wait for the user to press Enter or Space to restart
    if (input.IsHardDropRequested() || ::IsKeyPressed(KEY_ENTER))
    {
        // Swap back to a fresh PlayState!
        m_stateManager->SwapState(std::make_unique<PlayState>(m_stateManager));
    }
}

void GameOverState::Update(double, AudioHandler&)
{
    // Do nothing - static screen
}

void GameOverState::Render(const Renderer&) const
{
    // We don't need the renderer to draw the board, we just draw our game over text.
    // In a real engine we'd pass this to the Renderer, but for a simple overlay Menu
    // drawing text directly simplifies the architecture since we don't have a UI system.
    
    int screenWidth = 500;
    int screenHeight = 620;

    const char* text1 = "GAME OVER";
    const char* text2 = "Press SPACE to Restart";

    int fontSize1 = 40;
    int fontSize2 = 20;

    int text1Width = ::MeasureText(text1, fontSize1);
    int text2Width = ::MeasureText(text2, fontSize2);

    ::DrawText(text1, (screenWidth - text1Width) / 2, screenHeight / 2 - 40, fontSize1, RED);
    ::DrawText(text2, (screenWidth - text2Width) / 2, screenHeight / 2 + 10, fontSize2, RAYWHITE);
}
