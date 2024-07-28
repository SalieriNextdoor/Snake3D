#ifndef SCORE_H
#define SCORE_H

#include <string>

#include "constants.h"

class Score {
  using SELF = Score;

  unsigned long score;
  int max_score_digits;
  std::string scoreStr;

  SELF& makeScoreStr();

 public:
  Score(unsigned long startingScore = 0,
        int max_score_digits = scoreConstants::max_score_digits);

  SELF& updateScore(unsigned long val = 1);

  unsigned long getScore();
  std::string& getScoreStr();
};

#endif
