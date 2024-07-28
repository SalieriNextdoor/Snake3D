#include "Score.h"

#include <iostream>

using SELF = Score;

Score::Score(unsigned long startingScore, int _max_score_digits)
    : score{startingScore}, max_score_digits{_max_score_digits} {
  makeScoreStr();
}

SELF& Score::updateScore(unsigned long val) {
  score += val;
  makeScoreStr();
  return *this;
}

SELF& Score::makeScoreStr() {
  scoreStr = std::to_string(score);
  std::string temp;
  for (size_t i = 0; i < max_score_digits - scoreStr.size(); i++) temp += '0';
  scoreStr = temp + scoreStr;
  return *this;
}

unsigned long Score::getScore() { return score; }
std::string& Score::getScoreStr() { return scoreStr; }
