// tetromino_data.h
//
// Defines the exact shape of all 7 Tetrominoes as compile-time constants.
//
// ============================================================
// LEARNING OBJECTIVES (Phase 5)
// ============================================================
// - Data-Oriented Design over Object-Oriented Design:
//   Instead of creating an abstract base class `Tetromino` and 7 derived
//   classes (`IPiece`, `TPiece`, etc.), we treat all pieces identically.
//   They are just the concept of a "Pivot point + 4 relative offsets".
//   This avoids virtual function overhead, vtable pointers, and memory
//   fragmentation, while making the logic generic and mathematically pure.
//
// - constexpr data tables:
//   This entire file is `constexpr`. It calculates nothing at runtime.
//   In a micro-controller or retro console, this data gets burned directly
//   into Read-Only Memory (ROM) and takes up exactly zero RAM.
// ============================================================

#pragma once

#include "types.h"
#include <array>

namespace PieceData
{
    // A Tetromino is made of exactly 4 blocks.
    using ShapeOffsets = std::array<Position, 4>;

    // We define each piece centered around a "pivot" point (0, 0).

    // Note: y increases DOWNWARD (standard 2D graphics/grid convention).

    // I Piece (cyan)
    // [ ][pivot][ ][ ]
    inline constexpr ShapeOffsets SHAPE_I = {
        Position{-1, 0}, Position{0, 0}, Position{1, 0}, Position{2, 0}
    };

    // O Piece (yellow)
    // [pivot][ ]
    // [     ][ ]
    inline constexpr ShapeOffsets SHAPE_O = {
        Position{0, 0}, Position{1, 0}, Position{0, 1}, Position{1, 1}
    };

    // T Piece (purple)
    //    [ ]
    // [ ][pivot][ ]
    inline constexpr ShapeOffsets SHAPE_T = {
        Position{0, -1}, Position{-1, 0}, Position{0, 0}, Position{1, 0}
    };

    // S Piece (green)
    //    [ ][ ]
    // [ ][pivot]
    inline constexpr ShapeOffsets SHAPE_S = {
        Position{0, -1}, Position{1, -1}, Position{-1, 0}, Position{0, 0}
    };

    // Z Piece (red)
    // [ ][ ]
    //    [pivot][ ]
    inline constexpr ShapeOffsets SHAPE_Z = {
        Position{-1, -1}, Position{0, -1}, Position{0, 0}, Position{1, 0}
    };

    // J Piece (blue)
    // [ ]
    // [ ][pivot][ ]
    inline constexpr ShapeOffsets SHAPE_J = {
        Position{-1, -1}, Position{-1, 0}, Position{0, 0}, Position{1, 0}
    };

    // L Piece (orange)
    //          [ ]
    // [ ][pivot][ ]
    inline constexpr ShapeOffsets SHAPE_L = {
        Position{1, -1}, Position{-1, 0}, Position{0, 0}, Position{1, 0}
    };

    // Helper function to map a PieceType enum to its layout array.
    [[nodiscard]] inline constexpr ShapeOffsets GetShape(PieceType type)
    {
        switch (type)
        {
            case PieceType::I: return SHAPE_I;
            case PieceType::O: return SHAPE_O;
            case PieceType::T: return SHAPE_T;
            case PieceType::S: return SHAPE_S;
            case PieceType::Z: return SHAPE_Z;
            case PieceType::J: return SHAPE_J;
            case PieceType::L: return SHAPE_L;
            default:           return SHAPE_I; // Safe fallback
        }
    }

    // Helper to map a PieceType to its defining CellState (color)
    [[nodiscard]] inline constexpr CellState GetColor(PieceType type)
    {
        switch (type)
        {
            case PieceType::I: return CellState::Cyan;
            case PieceType::O: return CellState::Yellow;
            case PieceType::T: return CellState::Purple;
            case PieceType::S: return CellState::Green;
            case PieceType::Z: return CellState::Red;
            case PieceType::J: return CellState::Blue;
            case PieceType::L: return CellState::Orange;
            default:           return CellState::Empty;
        }
    }
}
