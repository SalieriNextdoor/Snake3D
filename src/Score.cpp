/**
 * @file Score.cpp
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Implements the class for the Score.
 */
#include "Score.h"

#include <iostream>

using SELF = Score;

Score::Score(unsigned long startingScore, int _max_score_digits)
    : score{startingScore}, max_score_digits{_max_score_digits} {
  makeScoreStr();
}

/**
 * The scoreStr is updated along with the score value.
 *
 * @see Score::makeScoreStr
 */
SELF& Score::updateScore(unsigned long val) {
  score += val;
  makeScoreStr();
  return *this;
}

/**
 * The string is created with trailing zeroes, according to max_score_digits,
 * and assigned to scoreStr.
 */
SELF& Score::makeScoreStr() {
  scoreStr = std::to_string(score);
  std::string temp;
  for (size_t i = 0; i < max_score_digits - scoreStr.size(); i++) temp += '0';
  scoreStr = temp + scoreStr;
  return *this;
}

unsigned long Score::getScore() { return score; }
std::string& Score::getScoreStr() { return scoreStr; }
