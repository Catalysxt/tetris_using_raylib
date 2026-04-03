// ============================================================
// LEARNING OBJECTIVES (Phase 4)
// ============================================================
// - Value Types:
//   Position is a fundamental value type. Like an 'int', you pass it
//   around by value, copy it, and compare it. Overloading operator==
//   and operator+ makes the math clean: `pos1 + pos2` instead of
//   `pos1.x + pos2.x`, `pos1.y + pos2.y`.
//

#pragma once

#include <cstdint>

// Represents every possible state a cell on the board can be in.
enum class CellState : uint8_t
{
    Empty,
    Cyan,       // I piece
    Blue,       // J piece
    Orange,     // L piece
    Yellow,     // O piece
    Green,      // S piece
    Purple,     // T piece
    Red         // Z piece
};

// Represents a mathematical 2D coordinate on the logical grid.
// Notice there are no Raylib dependencies here — this is pure logic.
struct Position
{
    int x; // Column
    int y; // Row

    // Operator overloads allow us to use + and == just like primitive types.
    
    // Checks if two positions are identical.
    // The 'const' at the end means calling this doesn't change either object.
    bool operator==(const Position& other) const
    {
        return x == other.x && y == other.y;
    }

    // Adds two positions together (useful for applying relative offsets
    // to a piece's origin).
    Position operator+(const Position& other) const
    {
        return {x + other.x, y + other.y};
    }
};

// Represents the 7 classic Tetromino shapes.
// Count is a common C++ trick to automatically know how many enum values exist.
enum class PieceType : uint8_t
{
    I, O, T, S, Z, J, L,
    Count
};
