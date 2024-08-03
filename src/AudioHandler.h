/**
 * @file AudioHandler.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Declares the class for audio handling.
 */
#ifndef AUDIO_HANDLER_H
#define AUDIO_HANDLER_H
#include <string>

#include "constants.h"

/**
 * @brief Defines the methods for playing .wav audio files.
 */
class AudioHandler {
  bool play_audio;

 public:
  /**
   * @brief Constructor for the audio handler.
   *
   * @param _play_audio whether or not audio should be played on call
   *
   */
  AudioHandler(bool _play_audio = true) : play_audio{_play_audio} {}
  AudioHandler(const AudioHandler& other) = delete;
  AudioHandler& operator=(const AudioHandler&) = delete;

  /**
   * @brief Plays a .wav audio to the desired volume if play_audio is true.
   *
   * @param filePath the path of the .wav file
   * @param volume the desired volume of play, ranging from 0.0 to 1.0
   *
   * @return the value of play_audio
   *
   * The function runs until completion of the file or until play_audio is
   * changed to false.
   */
  bool playAudio(const std::string& filePath, double volume);
  /**
   * @brief Enables audio playback. Changes play_audio to true.
   */
  void activateAudio();
  /**
   * @brief Disables audio playback. Changes play_audio to false.
   */
  void stopAudio();
};

#endif
