/*
 *  sounds.h
 *  teapots
 *
 *  Created by Ben Wadsworth on 28/07/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <OpenAL/al.h>

void initOpenAL();
void openWAV(char* fileName, ALuint* dest);
static inline ALenum GetFormatFromInfo(short channels, short bitsPerSample);
static void file_ignore_bytes(FILE* file, short bytes);
static unsigned char* file_allocate_and_read_bytes(FILE* file, size_t chunkSize);
static short file_read_int16_le(char* buffer, FILE* file);
static unsigned int file_read_int32_le(char* buffer, FILE* file);
template <typename T> T byte_reverse(T in);
static void dumpWholeFile(FILE* file);
void playHitSound();
void playSpinSound();
void playDeadSound();
void playScoreSound();
void playMusic();
void GetALErrorString(ALenum err);
void GetALCErrorString(ALenum err);
void muteMusic();
void unmuteMusic();