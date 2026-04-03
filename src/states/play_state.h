
// The main gameplay state — this is where Tetris actually happens.
// Right now it's a minimal stub that proves the state machine works.
// In later phases, it will own the Board, active Tetromino, and scoring.

#pragma once

#include "../core/game_state.h"
#include "../game/board.h"
#include "../game/piece_factory.h"
#include "../game/score_tracker.h"

// Forward declare to avoid circular includes
class StateManager;
class AudioHandler;

class PlayState : public GameState
{
public:
    // AudioHandler is injected here so HandleInput can trigger sounds
    // without needing to change the GameState interface signature.
    explicit PlayState(StateManager* stateManager, AudioHandler* audio);

    void OnEnter() override;
    void OnExit() override;
    void HandleInput(const InputHandler& input) override;
    void Update(double dt, AudioHandler& audio) override;
    void Render(const Renderer& renderer) const override;

private:
    // --- Phase 1: Collision ---
    // Evaluates if a given piece's absolute blocks overlap with walls, 
    // the floor, or existing locked blocks on the board.
    [[nodiscard]] bool IsValidPosition(const Tetromino& piece) const;

    // --- Phase 2: Gravity & Locking ---
    // Handles what happens when a piece hits the floor or another block.
    void LockPiece(AudioHandler& audio);

    StateManager* m_stateManager;
    // Non-owning pointer — Application owns the AudioHandler lifetime
    AudioHandler* m_audio;

    Board m_board;
    PieceFactory m_factory;
    Tetromino m_activePiece;
    ScoreTracker m_score;
    
    // Time in seconds between automatic piece drops
    double m_fallInterval = 1.0; 
    // Time remaining until the next automatic drop
    double m_fallTimer = 1.0;
};
