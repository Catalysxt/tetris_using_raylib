// renderer.cpp
//
// Implements the coordinate translation and raw Raylib draw calls.

#include "renderer.h"
#include <string>

void Renderer::BeginFrame() const
{
    ::BeginDrawing();
    ::ClearBackground(RenderConfig::BG_COLOR_MAIN);
}

void Renderer::EndFrame() const
{
    ::EndDrawing();
}

void Renderer::DrawBoardOutline() const
{
    // Draw the dark background inside the play area
    ::DrawRectangle(
        RenderConfig::BOARD_OFFSET_X, 
        RenderConfig::BOARD_OFFSET_Y, 
        RenderConfig::BOARD_WIDTH_PX, 
        RenderConfig::BOARD_HEIGHT_PX, 
        RenderConfig::BG_COLOR_BOARD
    );

    // Draw the thick outer border
    ::DrawRectangleLinesEx(
        {
            static_cast<float>(RenderConfig::BOARD_OFFSET_X - RenderConfig::BOARD_BORDER_THICKNESS),
            static_cast<float>(RenderConfig::BOARD_OFFSET_Y - RenderConfig::BOARD_BORDER_THICKNESS),
            static_cast<float>(RenderConfig::BOARD_WIDTH_PX + (RenderConfig::BOARD_BORDER_THICKNESS * 2)),
            static_cast<float>(RenderConfig::BOARD_HEIGHT_PX + (RenderConfig::BOARD_BORDER_THICKNESS * 2))
        },
        static_cast<float>(RenderConfig::BOARD_BORDER_THICKNESS),
        RenderConfig::BOARD_BORDER
    );

    // Draw the faint grid lines to give it that classic Tetris feel
    for (int col = 1; col < RenderConfig::BOARD_COLS; ++col)
    {
        int x = RenderConfig::BOARD_OFFSET_X + (col * RenderConfig::CELL_SIZE);
        ::DrawLine(x, RenderConfig::BOARD_OFFSET_Y, x, RenderConfig::BOARD_OFFSET_Y + RenderConfig::BOARD_HEIGHT_PX, RenderConfig::GRID_LINE_COLOR);
    }

    for (int row = 1; row < RenderConfig::BOARD_ROWS; ++row)
    {
        int y = RenderConfig::BOARD_OFFSET_Y + (row * RenderConfig::CELL_SIZE);
        ::DrawLine(RenderConfig::BOARD_OFFSET_X, y, RenderConfig::BOARD_OFFSET_X + RenderConfig::BOARD_WIDTH_PX, y, RenderConfig::GRID_LINE_COLOR);
    }
}

void Renderer::DrawPlaceholderCell(int gridX, int gridY, Color color) const
{
    // Translate from logic-space (grid coordinates) to screen-space (pixels)
    // The game logic thinks in 0-9 (col) and 0-19 (row).
    // We convert that to physical pixels on the monitor.
    int pixelX = RenderConfig::BOARD_OFFSET_X + (gridX * RenderConfig::CELL_SIZE);
    int pixelY = RenderConfig::BOARD_OFFSET_Y + (gridY * RenderConfig::CELL_SIZE);

    // Draw the main filled block
    ::DrawRectangle(pixelX, pixelY, RenderConfig::CELL_SIZE, RenderConfig::CELL_SIZE, color);

    // Draw a dark inner border to give the block some visual texture/separation
    ::DrawRectangleLinesEx(
        {
            static_cast<float>(pixelX + 1),
            static_cast<float>(pixelY + 1),
            static_cast<float>(RenderConfig::CELL_SIZE - 2),
            static_cast<float>(RenderConfig::CELL_SIZE - 2)
        },
        2.0f,
        { 0, 0, 0, 100 } // Semi-transparent black over the color
    );
}

void Renderer::DrawBoard(const Board& board) const
{
    // Iterate over the mathematical grid.
    const auto& grid = board.GetGrid();
    for (int row = 0; row < Board::ROWS; ++row)
    {
        for (int col = 0; col < Board::COLS; ++col)
        {
            if (grid[row][col] != CellState::Empty)
            {
                // Translate the abstract logic state into a physical color
                Color cellColor = GetCellColor(grid[row][col]);
                
                // Use our existing method to map the coordinate to pixels
                DrawPlaceholderCell(col, row, cellColor);
            }
        }
    }
}

void Renderer::DrawPiece(const Tetromino& piece) const
{
    // The renderer doesn't care about rotation logic or pivots.
    // It simply asks the Tetromino: "Where are your 4 blocks right now?"
    auto positions = piece.GetAbsolutePositions();
    Color pieceColor = GetCellColor(piece.GetColor());

    for (const auto& pos : positions)
    {
        // Tetrominoes can spawn slightly above the board before they
        // fully enter. We shouldn't draw blocks that are 'above' the
        // visible play area (row < 0).
        if (pos.y >= 0)
        {
            DrawPlaceholderCell(pos.x, pos.y, pieceColor);
        }
    }
}

void Renderer::DrawScoreOverlay(const ScoreTracker& track) const
{
    // C++ std::string formatting to safely convert our ints to text
    std::string scoreText = "SCORE:\n" + std::to_string(track.GetScore());
    std::string levelText = "LEVEL:\n" + std::to_string(track.GetLevel());
    std::string linesText = "LINES:\n" + std::to_string(track.GetLines());

    // Draw parameters
    int fontSize = 20;
    Color textColor = RAYWHITE;

    // Utilize the constexpr layout variables from RenderConfig
    // Raylib's C API uses C-style strings, so we call .c_str()
    ::DrawText(scoreText.c_str(), RenderConfig::UI_OFFSET_X, RenderConfig::UI_OFFSET_Y, fontSize, textColor);
    
    ::DrawText(levelText.c_str(), RenderConfig::UI_OFFSET_X, RenderConfig::UI_OFFSET_Y + 60, fontSize, textColor);

    ::DrawText(linesText.c_str(), RenderConfig::UI_OFFSET_X, RenderConfig::UI_OFFSET_Y + 120, fontSize, textColor);
}

Color Renderer::GetCellColor(CellState state) const
{
    switch (state)
    {
        case CellState::Cyan:   return { 0, 255, 255, 255 };     // I
        case CellState::Blue:   return { 0, 0, 255, 255 };       // J
        case CellState::Orange: return { 255, 165, 0, 255 };     // L
        case CellState::Yellow: return { 255, 255, 0, 255 };     // O
        case CellState::Green:  return { 0, 255, 0, 255 };       // S
        case CellState::Purple: return { 128, 0, 128, 255 };     // T
        case CellState::Red:    return { 255, 0, 0, 255 };       // Z
        default:                return BLANK;
    }
}
