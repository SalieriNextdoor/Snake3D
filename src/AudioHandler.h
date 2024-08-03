#ifndef AUDIO_HANDLER_H
#define AUDIO_HANDLER_H
#include <string>

#include "constants.h"

class AudioHandler {
  bool play_audio;

 public:
  AudioHandler(bool _play_audio = true) : play_audio{_play_audio} {}
  AudioHandler(const AudioHandler& other) = delete;
  AudioHandler& operator=(const AudioHandler&) = delete;

  void activateAudio();
  bool playAudio(const std::string& filePath, double volume);
  void stopAudio();
};

#endif
