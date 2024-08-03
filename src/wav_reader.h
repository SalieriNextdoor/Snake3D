#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

typedef struct {
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
} wav_file_data;

int wav_read(const char *file_path, wav_file_data *data) {
  FILE *audio;
  int nread;
  char riff[4], wave[4], fmt_id[4], data_id[4];
  unsigned long bloc_size = 0;

  audio = fopen(file_path, "rb");
  if (audio == NULL) {
    perror("Audio file %s couldn't be opened");
    return -1;
  }

  nread = fread(riff, 1, 4, audio);
  if (nread < 4) {
    fprintf(stderr, "File couldn't be properly read: fields 1-4\n");
    return -1;
  }

  if (!(riff[0] == 'R' && riff[1] == 'I' && riff[2] == 'F' && riff[3] == 'F')) {
    fprintf(stderr, "Invalid file: not a RIFF file.\n");
    return -1;
  }

  nread = fread(&data->FileSize, 4, 1, audio);
  if (nread < 1) {
    fprintf(stderr, "File couldn't be properly read: fields 5-8\n");
    return -1;
  }

  nread = fread(wave, 1, 4, audio);
  if (nread < 4) {
    fprintf(stderr, "File couldn't be properly read: fields 9-12\n");
    return -1;
  }

  if (!(wave[0] == 'W' && wave[1] == 'A' && wave[2] == 'V' && wave[3] == 'E')) {
    fprintf(stderr, "Invalid file: not a WAVE file.\n");
    return -1;
  }

  nread = fread(fmt_id, 1, 4, audio);
  if (nread < 4) {
    fprintf(stderr, "File couldn't be properly read: fields 13-16\n");
    return -1;
  }

  if (!(fmt_id[0] == 'f' && fmt_id[1] == 'm' && fmt_id[2] == 't' &&
        fmt_id[3] == ' ')) {
    fprintf(stderr, "Invalid file: format id missing.\n");
    return -1;
  }

  nread = fread(&bloc_size, 4, 1, audio);
  if (nread < 1) {
    fprintf(stderr, "File couldn't be properly read: fields 17-20\n");
    return -1;
  }

  if (bloc_size != 16) {
    printf("Invalid format block size of size %lu.\n", bloc_size);
    return -1;
  }

  nread = fread(&data->AudioFormat, 2, 1, audio);
  if (nread < 1) {
    fprintf(stderr, "File couldn't be properly read: fields 21-22\n");
    return -1;
  }

  nread = fread(&data->NbrChannels, 2, 1, audio);
  if (nread < 1) {
    fprintf(stderr, "File couldn't be properly read: fields 23-24\n");
    return -1;
  }

  nread = fread(&data->Frequence, 4, 1, audio);
  if (nread < 1) {
    fprintf(stderr, "File couldn't be properly read: fields 25-28\n");
    return -1;
  }

  nread = fread(&data->BytesPerSec, 4, 1, audio);
  if (nread < 1) {
    fprintf(stderr, "File couldn't be properly read: fields 29-32\n");
    return -1;
  }

  nread = fread(&data->BytesPerBloc, 2, 1, audio);
  if (nread < 1) {
    fprintf(stderr, "File couldn't be properly read: fields 33-34\n");
    return -1;
  }

  nread = fread(&data->BytesPerSample, 2, 1, audio);
  if (nread < 1) {
    fprintf(stderr, "File couldn't be properly read: fields 35-36\n");
    return -1;
  }

  // skip LIST blocks
  for (;;) {
    nread = fread(data_id, 1, 4, audio);
    if (nread < 4) {
      fprintf(stderr, "File couldn't be properly read: fields 37-40\n");
      return -1;
    }

    if (data_id[0] == 'L' && data_id[1] == 'I' && data_id[2] == 'S' &&
        data_id[3] == 'T') {
      unsigned long list_size = 0;
      nread = fread(&list_size, 4, 1, audio);
      if (nread < 1) {
        fprintf(stderr, "File couldn't be properly read: LIST field\n");
        return -1;
      }

      fseek(audio, list_size, SEEK_CUR);
    } else
      break;
  }

  if (!(data_id[0] == 'd' && data_id[1] == 'a' && data_id[2] == 't' &&
        data_id[3] == 'a')) {
    fprintf(stderr, "Invalid file: data id missing.\n");
    return -1;
  }

  nread = fread(&data->DataSize, 4, 1, audio);
  if (nread < 1) {
    fprintf(stderr, "File couldn't be properly read: fields 41-44\n");
    return -1;
  }

  data->SampledData = audio;

  return 0;
}

#ifdef __cplusplus
}
#endif
