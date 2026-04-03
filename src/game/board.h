// board.h
//
// The purely logical representation of the Tetris grid.
// 
// - std::array for bounds safety and value semantics:
//   Unlike a C-style array (`CellState grid[20][10]`), std::array knows
//   its own size, won't decay into a pointer, and can be copied with
//   a simple `=` assignment.
// 
// - [[nodiscard]]:
//   Tells the compiler to issue a warning if someone calls a method like
//   `IsOccupied()` but ignores the returned boolean. This catches bugs
//   where someone intended to mutate state but called a query instead.

#pragma once

#include "types.h"
#include <array>
#include <optional>

class Board
{
public:
    static constexpr int ROWS = 20;
    static constexpr int COLS = 10;

    // The grid is a 2D array. A nested array in an array. 
    // NOTE: Rather than grid[row][column], it's the other way around.
    // This is a quirk of working with arrays.
    using Grid = std::array<std::array<CellState, COLS>, ROWS>;

    // Constructor resets the board
    Board();

    // Resets the board to an empty state (used for game over -> restart)
    void Reset();

    // --- Queries (const, nodiscard) ---

    // Checks if a given row/col coordinate is inside the 10x20 grid.
    [[nodiscard]] bool IsWithinBounds(int row, int col) const;

    // Checks if the cell contains something other than Empty.
    // Returns true if the cell is occupied 
    [[nodiscard]] bool IsOccupied(int row, int col) const;

    // Returns the explicit type of the cell.
    // We return std::optional because someone might ask for a cell outside
    // the bounds! Instead of crashing (undefined behavior) or returning a
    // fake dummy value, std::optional forces the caller to acknowledge the
    // possibility of failure.
    [[nodiscard]] std::optional<CellState> GetCell(int row, int col) const;

    [[nodiscard]] bool IsRowFull(int row) const;
    [[nodiscard]] bool IsRowEmpty(int row) const;

    // Exposes the grid as read-only, specifically so the Renderer can
    // iterate over it to draw the blocks.
    [[nodiscard]] const Grid& GetGrid() const;

    // --- Mutations ---

    // Sets a specific cell to a specific state.
    // Does nothing if the coordinates are out of bounds.
    void SetCell(int row, int col, CellState state);

    // Scans the board for full rows, removes them, pulls upper rows down,
    // and returns the number of rows cleared (for scoring).
    int ClearFullRows();

private:
    // Helper used by ClearFullRows
    void MoveRowDown(int row, int numRows);

    Grid m_grid;
};
