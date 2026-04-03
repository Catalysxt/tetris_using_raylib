// piece_factory.cpp

#include "piece_factory.h"

PieceFactory::PieceFactory()
{
    // Seed the random number generator using the system clock
    std::random_device rd;
    m_rng = std::mt19937(rd());
    
    // We want a number from 0 to 6 (the 7 pieces in the PieceType enum)
    m_dist = std::uniform_int_distribution<int>(0, static_cast<int>(PieceType::Count) - 1);
}

Tetromino PieceFactory::CreatePiece(PieceType type) const
{
    // Standard Tetris spawn position is Row 0, Col 4 (top center)
    return Tetromino(type, Position{4, 0});
}

Tetromino PieceFactory::CreateRandomPiece()
{
    int randomTypeInt = m_dist(m_rng);
    PieceType randomType = static_cast<PieceType>(randomTypeInt);
    
    return CreatePiece(randomType);
}
