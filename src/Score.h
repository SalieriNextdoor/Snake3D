/**
 * @file Score.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Declares the class for the Score.
 */
#ifndef SCORE_H
#define SCORE_H

#include <string>

#include "constants.h"
/**
 * @brief Defines the methods for the representation of the Score, according to
 * the Point caught.
 *
 * @see snake::Snake::pointCollisionHead
 * @see snake::Snake::pointCollisionAll
 * @see Point
 */

class Score {
  using SELF = Score;

  unsigned long score;
  int max_score_digits;
  std::string scoreStr;

  /**
   * @brief Create a string of the current score.
   *
   * @return reference to the object
   */
  SELF& makeScoreStr();

 public:
  /**
   * @brief Constructor for the Point.
   *
   * @param startingScore the starting score value
   * @param max_score_digits the max amount of digits the score will have
   */
  Score(unsigned long startingScore = 0,
        int max_score_digits = scoreConstants::max_score_digits);

  /**
   * @brief Update the Score value.
   *
   * @param val the increment for the score
   *
   * @return reference to the object
   */
  SELF& updateScore(unsigned long val = 1);

  /**
   * @brief Get the Score value.
   *
   * @return the Score value
   */
  unsigned long getScore();
  /**
   * @brief Get the string representation of the Score.
   *
   * @return the string representation of the Score
   */
  std::string& getScoreStr();
};

#endif
