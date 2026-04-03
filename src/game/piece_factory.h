
// Encapsulates the logic for creating Tetrominoes.
//
// ============================================================
// LEARNING OBJECTIVES (Phase 5)
// ============================================================
// - The Factory Pattern:
//   Tetromino generation doesn't occur in PlayState.
//   Rather we outsource it to the factory.
//   Right now, this factory just
//   picks a random piece. Later, we can upgrade it to use a "7-bag"
//   randomizer (the official Tetris algorithm).
//   PlayState has no idea how tetrominoes are generated.
// ============================================================

#pragma once

#include "tetromino.h"

// For standard random number generation
#include <random>

class PieceFactory
{
public:
    PieceFactory();

    // Creates a specific piece type at the standard spawn location
    // (top-center of the 10x20 board).
    [[nodiscard]] Tetromino CreatePiece(PieceType type) const;

    // Returns a completely random piece.
    [[nodiscard]] Tetromino CreateRandomPiece();

private:
    // C++11 random number generation
    std::mt19937 m_rng;
    std::uniform_int_distribution<int> m_dist;
};
