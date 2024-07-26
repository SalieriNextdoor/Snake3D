#ifndef SCORE_H
#define SCORE_H

#include <string>

class Score {
  using SELF = Score;

  unsigned long score;
  std::string scoreStr;

 public:
  Score(unsigned long startingScore = 0);

  SELF& updateScore(unsigned long val = 1);

  std::string& getScore();
};

#endif
