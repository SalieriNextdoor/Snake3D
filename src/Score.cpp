#include "Score.h"

#include <iostream>

using SELF = Score;

Score::Score(unsigned long startingScore)
    : score{startingScore}, scoreStr{std::to_string(startingScore)} {}

SELF& Score::updateScore(unsigned long val) {
  score += val;
  scoreStr = std::to_string(score);
  return *this;
}

std::string& Score::getScore() { return scoreStr; }
