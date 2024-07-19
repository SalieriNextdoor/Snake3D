#ifndef SCORE_H
#define SCORE_H

class Score {
  using SELF = Score;

  unsigned long score;

 public:
  Score(unsigned long startingScore = 0);

  SELF& updateScore(unsigned long val = 1);

  SELF& printScore();
};

#endif
