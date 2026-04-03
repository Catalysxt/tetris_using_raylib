// board.cpp
//
// Implementation of the pure-logic Tetris board.
// Notice there are ZERO Raylib functions in this file. The `Board` class
// simply manages a grid of abstract colors (`CellState`).

#include "board.h"

Board::Board()
{
    Reset();
}

void Board::Reset()
{
    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLS; ++col)
        {
            m_grid[row][col] = CellState::Empty;
        }
    }
}

bool Board::IsWithinBounds(int row, int col) const
{
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

// Constrain tetromino to boundaries of the grid and to prevent collision. 
bool Board::IsOccupied(int row, int col) const
{

    // Pieces can't move through walls or the floor.
    if (!IsWithinBounds(row, col))
    {
        return true; // Early return
    }

    // Return if the cell is occupied or not
    return m_grid[row][col] != CellState::Empty;
}

std::optional<CellState> Board::GetCell(int row, int col) const
{
    if (!IsWithinBounds(row, col))
    {
        return std::nullopt; // Safely indicate failure to access
    }

    return m_grid[row][col];
}

bool Board::IsRowFull(int row) const
{
    if (row < 0 || row >= ROWS) return false;

    for (int col = 0; col < COLS; ++col)
    {
        if (m_grid[row][col] == CellState::Empty)
        {
            return false;
        }
    }
    return true;
}

bool Board::IsRowEmpty(int row) const
{
    if (row < 0 || row >= ROWS) return false;

    for (int col = 0; col < COLS; ++col)
    {
        if (m_grid[row][col] != CellState::Empty)
        {
            return false;
        }
    }
    return true;
}

const Board::Grid& Board::GetGrid() const
{
    return m_grid;
}

void Board::SetCell(int row, int col, CellState state)
{
    if (IsWithinBounds(row, col))
    {
        m_grid[row][col] = state;
    }
}

int Board::ClearFullRows()
{
    int clearedCount = 0;

    // We scan from bottom to top.
    for (int row = ROWS - 1; row >= 0; )
    {
        if (IsRowFull(row))
        {
            clearedCount++;
            
            // Move everything above this row down by 1.
            // Notice we don't decrement 'row' here, because after moving
            // rows down, the the current row index now contains the row that
            // used to be above it. We need to check this new row as well!
            MoveRowDown(row, 1);
        }
        else
        {
            // Only move up to check the next row if this one wasn't full
            row--;
        }
    }

    return clearedCount;
}

void Board::MoveRowDown(int row, int numRows)
{
    // Start at the specified row and work our way up
    for (int r = row; r >= numRows; --r)
    {
        // Copy the row from above
        m_grid[r] = m_grid[r - numRows];
    }

    // The topmost rows (that were pulled down) become empty
    for (int r = 0; r < numRows; ++r)
    {
        for (int c = 0; c < COLS; ++c)
        {
            m_grid[r][c] = CellState::Empty;
        }
    }
}
