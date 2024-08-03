#include "AudioHandler.h"

#ifdef __linux__
#include <alsa/asoundlib.h>

#include <cstdio>

struct wav_file_data {
  unsigned long FileSize;
  unsigned short AudioFormat;
  unsigned short NbrChannels;
  unsigned int Frequence;
  unsigned long BytesPerSec;
  unsigned short BytesPerBloc;
  unsigned short BytesPerSample;
  unsigned long DataSize;
  unsigned long ListSize;
  FILE *SampledData;
};

template <typename T>
inline T clamp(T val, T min, T max) {
  return (val < min) ? min : ((val > max) ? max : val);
}

bool wav_read(const char *file_path, wav_file_data *data) {
  FILE *audio;
  int nread;
  char riff[4], wave[4], fmt_id[4], data_id[4];
  unsigned long bloc_size = 0;

  audio = fopen(file_path, "rb");
  if (audio == NULL) {
    fprintf(stderr, "Audio file %s couldn't be opened: ", file_path);
    perror("");
    return false;
  }

  nread = fread(riff, 1, 4, audio);
  if (nread < 4) {
    fprintf(stderr, "File couldn't be properly read: fields 1-4\n");
    return false;
  }

  if (!(riff[0] == 'R' && riff[1] == 'I' && riff[2] == 'F' && riff[3] == 'F')) {
    fprintf(stderr, "Invalid file: not a RIFF file.\n");
    return false;
  }

  nread = fread(&data->FileSize, 4, 1, audio);
  if (nread < 1) {
    fprintf(stderr, "File couldn't be properly read: fields 5-8\n");
    return false;
  }

  nread = fread(wave, 1, 4, audio);
  if (nread < 4) {
    fprintf(stderr, "File couldn't be properly read: fields 9-12\n");
    return false;
  }

  if (!(wave[0] == 'W' && wave[1] == 'A' && wave[2] == 'V' && wave[3] == 'E')) {
    fprintf(stderr, "Invalid file: not a WAVE file.\n");
    return false;
  }

  nread = fread(fmt_id, 1, 4, audio);
  if (nread < 4) {
    fprintf(stderr, "File couldn't be properly read: fields 13-16\n");
    return false;
  }

  if (!(fmt_id[0] == 'f' && fmt_id[1] == 'm' && fmt_id[2] == 't' &&
        fmt_id[3] == ' ')) {
    fprintf(stderr, "Invalid file: format id missing.\n");
    return false;
  }

  nread = fread(&bloc_size, 4, 1, audio);
  if (nread < 1) {
    fprintf(stderr, "File couldn't be properly read: fields 17-20\n");
    return false;
  }

  if (bloc_size != 16) {
    printf("Invalid format block size of size %lu.\n", bloc_size);
    return false;
  }

  nread = fread(&data->AudioFormat, 2, 1, audio);
  if (nread < 1) {
    fprintf(stderr, "File couldn't be properly read: fields 21-22\n");
    return false;
  }

  nread = fread(&data->NbrChannels, 2, 1, audio);
  if (nread < 1) {
    fprintf(stderr, "File couldn't be properly read: fields 23-24\n");
    return false;
  }

  nread = fread(&data->Frequence, 4, 1, audio);
  if (nread < 1) {
    fprintf(stderr, "File couldn't be properly read: fields 25-28\n");
    return false;
  }

  nread = fread(&data->BytesPerSec, 4, 1, audio);
  if (nread < 1) {
    fprintf(stderr, "File couldn't be properly read: fields 29-32\n");
    return false;
  }

  nread = fread(&data->BytesPerBloc, 2, 1, audio);
  if (nread < 1) {
    fprintf(stderr, "File couldn't be properly read: fields 33-34\n");
    return false;
  }

  nread = fread(&data->BytesPerSample, 2, 1, audio);
  if (nread < 1) {
    fprintf(stderr, "File couldn't be properly read: fields 35-36\n");
    return false;
  }

  // skip LIST blocks
  for (;;) {
    nread = fread(data_id, 1, 4, audio);
    if (nread < 4) {
      fprintf(stderr, "File couldn't be properly read: fields 37-40\n");
      return false;
    }

    if (data_id[0] == 'L' && data_id[1] == 'I' && data_id[2] == 'S' &&
        data_id[3] == 'T') {
      unsigned long list_size = 0;
      nread = fread(&list_size, 4, 1, audio);
      if (nread < 1) {
        fprintf(stderr, "File couldn't be properly read: LIST field\n");
        return false;
      }

      fseek(audio, list_size, SEEK_CUR);
    } else
      break;
  }

  if (!(data_id[0] == 'd' && data_id[1] == 'a' && data_id[2] == 't' &&
        data_id[3] == 'a')) {
    fprintf(stderr, "Invalid file: data id missing.\n");
    return false;
  }

  nread = fread(&data->DataSize, 4, 1, audio);
  if (nread < 1) {
    fprintf(stderr, "File couldn't be properly read: fields 41-44\n");
    return false;
  }

  data->SampledData = audio;

  return true;
}

bool AudioHandler::playAudio(const std::string &filePath, double volume) {
  wav_file_data data{};
  int err;
  double seconds;
  char *buf;
  snd_pcm_t *playback_handle;
  snd_pcm_hw_params_t *hw_params;

  if (!wav_read(filePath.c_str(), &data)) return false;

  seconds = (double)data.DataSize / data.BytesPerSec;

  if ((err = snd_pcm_open(&playback_handle, audioConstants::pcm_device.c_str(),
                          SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
    fprintf(stderr, "cannot open audio device %s (%s)\n",
            audioConstants::pcm_device.c_str(), snd_strerror(err));
    return false;
  }

  if ((err = snd_pcm_hw_params_malloc(&hw_params)) < 0) {
    fprintf(stderr, "cannot allocate hardware parameter structure (%s)\n",
            snd_strerror(err));
    return false;
  }

  if ((err = snd_pcm_hw_params_any(playback_handle, hw_params)) < 0) {
    fprintf(stderr, "cannot initialize hardware parameter structure (%s)\n",
            snd_strerror(err));
    return false;
  }

  if ((err = snd_pcm_hw_params_set_access(playback_handle, hw_params,
                                          SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
    fprintf(stderr, "cannot set access type (%s)\n", snd_strerror(err));
    return false;
  }

  if ((err = snd_pcm_hw_params_set_format(playback_handle, hw_params,
                                          SND_PCM_FORMAT_S16_LE)) < 0) {
    fprintf(stderr, "cannot set sample format (%s)\n", snd_strerror(err));
    return false;
  }

  if ((err = snd_pcm_hw_params_set_rate_near(playback_handle, hw_params,
                                             &data.Frequence, 0)) < 0) {
    fprintf(stderr, "cannot set sample rate (%s)\n", snd_strerror(err));
    return false;
  }

  if ((err = snd_pcm_hw_params_set_channels(playback_handle, hw_params,
                                            data.NbrChannels)) < 0) {
    fprintf(stderr, "cannot set channel count (%s)\n", snd_strerror(err));
    return false;
  }

  if ((err = snd_pcm_hw_params(playback_handle, hw_params)) < 0) {
    fprintf(stderr, "cannot set parameters (%s)\n", snd_strerror(err));
    return false;
  }

  snd_pcm_uframes_t frames;
  snd_pcm_hw_params_get_period_size(hw_params, &frames, 0);

  unsigned int tmp;

  snd_pcm_hw_params_get_period_time(hw_params, &tmp, NULL);

  snd_pcm_format_t sampfmt;
  snd_pcm_hw_params_get_format(hw_params, &sampfmt);

  // division by 8 to convert from bits to bytes
  int sampwidth = snd_pcm_format_physical_width(sampfmt) / 8;

  int buf_size = frames * data.NbrChannels * sampwidth;
  buf = new char[buf_size];

  if (buf == NULL) {
    fprintf(stderr, "bad alloc\n");
    return false;
  }

  snd_pcm_hw_params_free(hw_params);

  for (unsigned long i = (int)(seconds * 1000000) / tmp; i > 0 && play_audio;
       i--) {
    int read;
    if ((read = fread(buf, sizeof(char), buf_size, data.SampledData)) == 0) {
      printf("Premature end of file.\n");
      break;
    }

    int16_t *samples = reinterpret_cast<int16_t *>(buf);
    for (int i = 0; i < read / sampwidth; ++i) {
      samples[i] = static_cast<int16_t>(samples[i] * volume);
    }

    if ((err = snd_pcm_writei(playback_handle, buf, frames)) == -EPIPE) {
      printf("XRUN.\n");
      snd_pcm_prepare(playback_handle);
    } else if (err < 0) {
      fprintf(stderr, "cannot write to pcm device (%s)\n", snd_strerror(err));
      return false;
    }
  }

  // snd_pcm_drain(playback_handle);
  while (snd_pcm_avail_update(playback_handle) > 0 && play_audio);
  snd_pcm_close(playback_handle);

  delete[] buf;
  fclose(data.SampledData);

  return play_audio;
}

void AudioHandler::activateAudio() { play_audio = true; }
void AudioHandler::stopAudio() { play_audio = false; }

#endif

