// renderer.h
//
// The single source of truth for translating game data into pixels.
//
// ============================================================
// LEARNING OBJECTIVES (Phase 3)
// ============================================================
// - Model-View-Controller (MVC) Separation:
//   The Renderer acts as the View. It does not own any game state.
//   It just reads data from the Model and calls Raylib functions.

// ============================================================

#pragma once

#include "render_config.h"
#include "../game/board.h"
#include "../game/tetromino.h"
#include "../game/score_tracker.h"
#include "../game/types.h"
#include <raylib.h>

class Renderer
{
public:
    Renderer() = default;
    
    // Non-copyable, similar to Application
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    // Everything is const since we don't want Renderer changing stuff
    
    // Wraps Raylib's BeginDrawing() and clears the screen
    void BeginFrame() const;
    
    // Wraps Raylib's EndDrawing()
    void EndFrame() const;

    // Draws an empty board (background + outer border + grid lines)
    void DrawBoardOutline() const;

    // Translates a purely logical abstract game board into colored pixels.
    void DrawBoard(const Board& board) const;

    // Translates the abstract logical piece into a set of rendering calls.
    void DrawPiece(const Tetromino& piece) const;

    // Draws the pure numerical data from the score tracker onto the screen.
    void DrawScoreOverlay(const ScoreTracker& scoreTracker) const;

    // Temporary method to prove coordinate translation works.
    void DrawPlaceholderCell(int gridX, int gridY, Color color) const;

private:
    // Helper to map an abstract CellState enum to a physical screen Color
    [[nodiscard]] Color GetCellColor(CellState state) const;
};
