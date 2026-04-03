// play_state.cpp
//
// Stub implementation of the gameplay state.
// Each method is a placeholder that will be expanded in later phases:
//   Phase 3: Render() will use the Renderer class
//   Phase 4: Update() will manage the Board
//   Phase 5: Will spawn Tetrominoes
//   Phase 6: HandleInput() will use the InputHandler

#include "play_state.h"
#include "game_over_state.h"
#include "../core/input_handler.h"
#include "../core/state_manager.h"
#include "../core/audio_handler.h"
#include "../rendering/renderer.h"
#include <raylib.h>

PlayState::PlayState(StateManager* stateManager, AudioHandler* audio)
    : m_stateManager(stateManager)
    , m_audio(audio)
{
}

void PlayState::OnEnter()
{
    // Spawn our first piece via the factory
    m_activePiece = m_factory.CreateRandomPiece();
    m_audio->PlayGameplayMusic();
}

void PlayState::OnExit()
{
    m_audio->StopGameplayMusic();
    // Future: save score, cleanup resources
}

void PlayState::HandleInput(const InputHandler& input)
{
    // In Phase 6, we finally bring the game to life!
    // We check the input handler for requests and apply them to the piece.

    // =================================================================
    // PHASE 1: COLLISION DETECTION
    // We create a duplicate, validate if it's a valid position.
    // If yes, perform the move
    // =================================================================

    if (input.IsMoveLeftRequested())
    {
        Tetromino testPiece = m_activePiece;
        testPiece.MoveLeft();
        if (IsValidPosition(testPiece))
        {
            m_activePiece = testPiece;
            // Only play the sound when the move actually went through.
            // We don't want a sound when bumping into a wall!
            m_audio->PlayMoveSound();
        }
    }
    else if (input.IsMoveRightRequested())
    {
        Tetromino testPiece = m_activePiece;
        testPiece.MoveRight();
        if (IsValidPosition(testPiece))
        {
            m_activePiece = testPiece;
            m_audio->PlayMoveSound();
        }
    }

    if (input.IsRotateCWRequested())
    {
        Tetromino testPiece = m_activePiece;
        testPiece.RotateCW();
        if (IsValidPosition(testPiece))
        {
            m_activePiece = testPiece;
            m_audio->PlayMoveSound();
        }
    }
    else if (input.IsRotateCCWRequested())
    {
        Tetromino testPiece = m_activePiece;
        testPiece.RotateCCW();
        if (IsValidPosition(testPiece))
        {
            m_activePiece = testPiece;
            m_audio->PlayMoveSound();
        }
    }

    // =================================================================
    // PHASE 2: FORCED DROP (Manual Gravity)
    // =================================================================
    if (input.IsForcedDropRequested())
    {
        Tetromino testPiece = m_activePiece;
        testPiece.MoveDown();
        if (IsValidPosition(testPiece))
        {
            m_activePiece = testPiece;
            
            // Reset the gravity timer so the piece doesn't double-drop immediately
            m_fallTimer = m_fallInterval;
        }
    }
}

bool PlayState::IsValidPosition(const Tetromino& piece) const
{
    // A Tetromino is internally just an enum and an origin point.
    // We ask it to run its rotation matrix math to give us the current
    // absolute grid coordinates of its 4 blocks.
    auto positions = piece.GetAbsolutePositions();

    for (const auto& pos : positions)
    {
        // Tetrominoes often spawn with a y-coordinate < 0 (above the board).
        // This is perfectly valid as they fall into view, so we only
        // check collisions for blocks that have entered the y >= 0 playfield.
        // The x-coordinate (walls) must ALWAYS be checked.
        
        // Let's protect against left/right walls even if above the board
        if (pos.x < 0 || pos.x >= Board::COLS)
        {
            return false;
        }

        if (pos.y >= 0)
        {
            // The Board treats walls, the floor, and locked blocks as "Occupied".
            // See Phase 4 learning notes for how this unifies collision!
            if (m_board.IsOccupied(pos.y, pos.x))
            {
                return false; // This area is invalid 
            }
        }
    }

    // If none of the 4 blocks collided, the position is valid!
    return true;
}

void PlayState::Update(double dt, AudioHandler& audio)
{
    // Raylib requires music streams to be updated every frame!
    audio.UpdateMusicStream();

    // =================================================================
    // PHASE 2: GRAVITY
    // =================================================================
    m_fallTimer -= dt;

    if (m_fallTimer <= 0.0)
    {
        m_fallTimer += m_fallInterval; // Reset timer for the next drop

        Tetromino testPiece = m_activePiece;
        testPiece.MoveDown();

        if (IsValidPosition(testPiece))
        {
            m_activePiece = testPiece; // Free fall
        }
        else
        {
            // The piece tried to fall but hit something! It's time to lock it.
            LockPiece(audio);
        }
    }
}

void PlayState::LockPiece(AudioHandler& audio)
{
    // 1. Imprint the piece onto the Board
    auto positions = m_activePiece.GetAbsolutePositions();
    CellState color = m_activePiece.GetColor();

    for (const auto& pos : positions)
    {
        // Only lock blocks that have actually entered the play area
        if (pos.y >= 0)
        {
            m_audio->PlayLockSound();
            m_board.SetCell(pos.y, pos.x, color); // Lock the tetromino into place
        }
    }

    // 2. Clear any completed lines
    // Notice how PlayState doesn't need to know *how* to shift array indices.
    // It just asks the Board to do it.
    int linesCleared = m_board.ClearFullRows();
    
    // Pass the receipts to the ScoreTracker
    if (linesCleared > 0)
    {
        m_score.AddClearedLines(linesCleared);
        // Note: As you reach higher levels, you can update `m_fallInterval` here to speed up the game!
        // e.g., m_fallInterval = 1.0 - ((m_score.GetLevel() - 1) * 0.05); (clamped to a minimum > 0)
        
        audio.PlayLineClearSound();
    }

    // 3. Spawn a new piece at the top
    m_activePiece = m_factory.CreateRandomPiece();

    // =================================================================
    // PHASE 5: GAME OVER CONDITION
    // =================================================================
    // If the newly spawned piece immediately collides with existing blocks,
    // the board is full and the game is over.
    if (!IsValidPosition(m_activePiece))
    {
        audio.PlayGameOverSound();
        m_stateManager->SwapState(std::make_unique<GameOverState>(m_stateManager, m_audio));
    }
}

void PlayState::Render(const Renderer& renderer) const
{
    // Draw the board perimeter
    renderer.DrawBoardOutline();

    // Draw the actual cells on the board
    renderer.DrawBoard(m_board);

    // Draw the active falling piece over the board
    renderer.DrawPiece(m_activePiece);

    // Draw the UI
    renderer.DrawScoreOverlay(m_score);

    // Debugging text 
    ::DrawFPS(10, 40);
}
