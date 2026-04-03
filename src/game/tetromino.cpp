// tetromino.cpp

#include "tetromino.h"
#include "tetromino_data.h"

Tetromino::Tetromino(PieceType type, Position spawnPos)
    : m_type(type), m_origin(spawnPos)
{
    // Look up the color for this specific piece type
    m_color = PieceData::GetColor(type);
}

void Tetromino::MoveDown()
{
    m_origin.y += 1; // y increases downwards in 2D graphics
}

void Tetromino::MoveLeft()
{
    m_origin.x -= 1;
}

void Tetromino::MoveRight()
{
    m_origin.x += 1;
}

void Tetromino::RotateCW()
{
    // The 'O' piece (yellow block) doesn't rotate!
    // Since it's a 2x2 square, rotation just returns the same shape.
    if (m_type == PieceType::O) return;

    m_rotationState = (m_rotationState + 1) % 4;
}

void Tetromino::RotateCCW()
{
    if (m_type == PieceType::O) return;

    m_rotationState = (m_rotationState - 1);
    if (m_rotationState < 0) 
    {
        m_rotationState = 3;
    }
}

std::array<Position, 4> Tetromino::GetAbsolutePositions() const
{
    std::array<Position, 4> absPos;
    
    // Get the base (unrotated) shape offsets for this piece type
    const auto baseOffsets = PieceData::GetShape(m_type);

    for (int i = 0; i < 4; ++i)
    {
        Position offset = baseOffsets[i];

        // Apply rotation transformations mathematically.
        // Standard 2D rotation matrix for increments of 90 degrees:
        // 90 deg CW:  (x, y) -> (-y,  x)
        // 180 deg:    (x, y) -> (-x, -y)
        // 270 deg (CCW): (x, y)->(y, -x)
        
        int x = offset.x;
        int y = offset.y;

        switch (m_rotationState)
        {
            case 0:
                // No rotation needed
                break;
            case 1: // 90 CW
                offset.x = -y;
                offset.y = x;
                break;
            case 2: // 180
                offset.x = -x;
                offset.y = -y;
                break;
            case 3: // 270 CW (or 90 CCW)
                offset.x = y;
                offset.y = -x;
                break;
        }

        // Add the transformed relative offset to the absolute pivot point
        absPos[i] = m_origin + offset;
    }

    return absPos;
}
