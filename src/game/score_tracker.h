// score_tracker.h
//
// Encapsulates the logic for tracking lines, calculating score, and level.
//
// ============================================================
// LEARNING OBJECTIVES (Phase 4)
// ============================================================
// - Composition over Inheritance:
//   Rather than making PlayState handle `score += 100 * level` math,
//   we compose a ScoreTracker into it. This keeps PlayState focused
//   on state transitions and leaves math to a dedicated component.
// ============================================================

#pragma once

class ScoreTracker
{
public:
    ScoreTracker() = default;

    // Call this specifically when lines are cleared simultaneously.
    void AddClearedLines(int count);

    // Call this if implementing a soft/hard drop score bonus.
    void AddDropScore(int points);

    [[nodiscard]] int GetScore() const { return m_score; }
    [[nodiscard]] int GetLevel() const { return m_level; }
    [[nodiscard]] int GetLines() const { return m_lines; }

private:
    int m_score = 0;
    int m_level = 1;
    int m_lines = 0;

    // Standard classic Tetris formula helpers
    int CalculateLineScore(int linesCleared) const;
    void UpdateLevel();
};
