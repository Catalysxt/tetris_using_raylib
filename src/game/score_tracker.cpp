// score_tracker.cpp

#include "score_tracker.h"

void ScoreTracker::AddClearedLines(int count)
{
    if (count <= 0) return;

    // 1. Add to total lines
    m_lines += count;

    // 2. Add to score based on the classic formula
    m_score += CalculateLineScore(count);

    // 3. Update level based on total lines
    UpdateLevel();
}

void ScoreTracker::AddDropScore(int points)
{
    m_score += points;
}

int ScoreTracker::CalculateLineScore(int linesCleared) const
{
    // Classic multiplier based on simultaneous lines cleared
    int baseVal = 0;
    switch (linesCleared)
    {
        case 1: baseVal = 100; break;
        case 2: baseVal = 300; break;
        case 3: baseVal = 500; break;
        case 4: baseVal = 800; break;
        default: break; // Protects against weird inputs
    }

    // Multiply by the current level for scaling difficulty
    return baseVal * m_level;
}

void ScoreTracker::UpdateLevel()
{
    // Level goes up every 10 lines
    // So if lines = 10..19, level is 2.
    m_level = (m_lines / 10) + 1;
}
