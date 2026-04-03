
// Represents an active, moving Tetromino piece on the board.
//
// ============================================================
// LEARNING OBJECTIVES (Phase 5)
// ============================================================
// - Value Semantics (again):
//   Tetromino is small enough to be copied freely. It holds no pointers
//   and manages no memory. It's essentially just:
//   (1 Enum + 1 Position + 1 Int = 8 bytes).
//
// - Math over Hardcoding:
//   Instead of storing 4 hardcoded arrays for each piece's rotation
//   states, we store 1 base array and generate the rotations using
//   2D mathematical transformations via a rotation matrix.
// ============================================================

#pragma once

#include "types.h"
#include <array>

class Tetromino
{
public:

    Tetromino() = default;

    // Constructs a specific piece at a specific starting position.
    Tetromino(PieceType type, Position spawnPos);

    // --- Queries ---
    
    [[nodiscard]] PieceType GetType() const { return m_type; }
    [[nodiscard]] CellState GetColor() const { return m_color; }
    
    // Returns the exact grid coordinates of all 4 blocks in the piece's
    // current position and rotation state.
    // This is computed on the fly by adding the relative offsets to the origin.
    [[nodiscard]] std::array<Position, 4> GetAbsolutePositions() const;

    // --- Mutations (Movement) ---
    // Note: These methods blindly move the piece. They do NOT check for 
    // collisions. The game logic (PlayState/InputHandler) takes care of that.

    void MoveDown();
    void MoveLeft();
    void MoveRight();
    
    // --- Mutations (Rotation) ---
    void RotateCW();
    void RotateCCW();

private:
    // Characteristics of a tetromino
    PieceType m_type = PieceType::I;
    CellState m_color = CellState::Empty;
    
    // The "pivot" point on the board.
    Position m_origin = {0, 0};
    
    // Current rotation state (0, 1, 2, or 3)
    // 0 = Spawn state, 1 = right, 2 = inverted, 3 = left
    int m_rotationState = 0;
};
