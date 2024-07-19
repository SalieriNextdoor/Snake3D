#include "Score.h"

#include <iostream>

using SELF = Score;

Score::Score(unsigned long startingScore) : score{startingScore} {}

SELF& Score::updateScore(unsigned long val) {
  score += val;
  return *this;
}

SELF& Score::printScore() {
  std::cout << "Score: " << score << std::endl;
  return *this;
}
