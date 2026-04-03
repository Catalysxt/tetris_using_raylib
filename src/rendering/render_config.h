
// Defines the visual theme and dimensions for the game.

#pragma once

#include <raylib.h>

struct RenderConfig
{
    // --- Layout ---
    // The size of a single square block on the grid (pixels)
    static constexpr int CELL_SIZE = 30;
    
    // The thickness of the border drawn around the entire board
    static constexpr int BOARD_BORDER_THICKNESS = 4;
    
    // Board dimensions (logical)
    static constexpr int BOARD_ROWS = 20;
    static constexpr int BOARD_COLS = 10;
    
    // Board dimensions (pixels).
    // Notice how we calculate this at compile time from the values above!
    static constexpr int BOARD_WIDTH_PX = BOARD_COLS * CELL_SIZE;
    static constexpr int BOARD_HEIGHT_PX = BOARD_ROWS * CELL_SIZE;
    
    // Where the top-left corner of the board sits on the screen (pixels)
    // For now we hardcode it to center the board in a 500x620 window
    static constexpr int BOARD_OFFSET_X = (500 - BOARD_WIDTH_PX) / 2;
    static constexpr int BOARD_OFFSET_Y = (620 - BOARD_HEIGHT_PX) / 2;

    // --- UI/Text Layout ---
    // Place the UI panel to the right of the board
    static constexpr int UI_OFFSET_X = BOARD_OFFSET_X + BOARD_WIDTH_PX + 25;
    static constexpr int UI_OFFSET_Y = BOARD_OFFSET_Y + 20;
    
    // --- Colors ---
    // We define a dark theme for the engine
    static constexpr Color BG_COLOR_MAIN = { 15, 15, 25, 255 };
    static constexpr Color BG_COLOR_BOARD = { 5, 5, 10, 255 };
    static constexpr Color BOARD_BORDER = { 50, 50, 70, 255 };
    static constexpr Color GRID_LINE_COLOR = { 30, 30, 45, 255 };
};
