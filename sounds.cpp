/*
 *  sounds.cpp
 *  teapots
 *
 *  Created by Ben Wadsworth on 28/07/2011.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <CoreFoundation/CoreFoundation.h>
#include "sounds.h"

ALuint hitSound;
ALuint spinSound;
ALuint deadSound;
ALuint scoreSound;
ALuint music;

void initOpenAL() {
	
	ALenum errorNum = alGetError();
	// initialise OpenAL
	ALCdevice* device = alcOpenDevice(NULL);
	ALCcontext* context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);
	
	errorNum = alGetError();
	
	alListener3f(AL_POSITION, 0, 0, 0);
	
	errorNum = alGetError();
	
	alListener3f(AL_VELOCITY, 0, 0, 0);
	
	errorNum = alGetError();
	
	ALfloat listenerOri[]={0.0,0.0,1.0, 0.0,1.0,0.0};
	
	alListenerfv(AL_ORIENTATION, listenerOri);
	
	errorNum = alGetError();
	
	alGenSources(1, &hitSound);
	alGenSources(1, &spinSound);
	alGenSources(1, &deadSound);
	alGenSources(1, &scoreSound);
	alGenSources(1, &music);
	
	errorNum = alGetError();
	
	alSourcef(hitSound, AL_PITCH, 1);
	alSourcef(spinSound, AL_PITCH, 1);
	alSourcef(deadSound, AL_PITCH, 1);
	alSourcef(scoreSound, AL_PITCH, 1);
	alSourcef(music, AL_PITCH, 1);
	
	alSourcef(hitSound, AL_GAIN, 1);
	alSourcef(spinSound, AL_GAIN, 1);
	alSourcef(deadSound, AL_GAIN, 0.4);
	alSourcef(scoreSound, AL_GAIN, 0.6);
	alSourcef(music, AL_GAIN, 0.4);
	
	alSource3f(hitSound, AL_POSITION, 0, 0, 0);
	alSource3f(spinSound, AL_POSITION, 0, 0, 0);
	alSource3f(deadSound, AL_POSITION, 0, 0, 0);
	alSource3f(scoreSound, AL_POSITION, 0, 0, 0);
	alSource3f(music, AL_POSITION, 0, 0, 0);
	
	alSource3f(hitSound, AL_VELOCITY, 0, 0, 0);
	alSource3f(spinSound, AL_VELOCITY, 0, 0, 0);
	alSource3f(deadSound, AL_VELOCITY, 0, 0, 0);
	alSource3f(scoreSound, AL_VELOCITY, 0, 0, 0);
	alSource3f(music, AL_VELOCITY, 0, 0, 0);
	
	alSourcei(hitSound, AL_LOOPING, AL_FALSE);
	alSourcei(spinSound, AL_LOOPING, AL_FALSE);
	alSourcei(deadSound, AL_LOOPING, AL_FALSE);
	alSourcei(scoreSound, AL_LOOPING, AL_FALSE);
	alSourcei(music, AL_LOOPING, AL_FALSE);
	
	errorNum = alGetError();
	
	openWAV("arcade.wav", &hitSound);
	openWAV("powerup.wav", &spinSound);
	openWAV("pulsegun.wav", &deadSound);
	openWAV("spaceship_hit.wav", &scoreSound);
	openWAV("depthcharge_music.wav", &music);
	
	printf("Error after alBufferData, before alSourcePlay: %x\n", alGetError());
	
	playMusic();
	
	errorNum = alGetError();
	if (errorNum != AL_NO_ERROR) {
		printf("Error starting playback: %x", errorNum);
	}
}

void openWAV(char* fileName, ALuint* dest) {
	alGetError();
	int errorNum = 0;
	
	ALuint buffer;
	alGenBuffers(1, &buffer);
	
	errorNum = alGetError();
	
	
	
	errorNum = alGetError();
	
	FILE* file;
	file = fopen(fileName, "r");
	if (file == NULL) {
		printf("File access error\n");
		exit(1);
	}
	
	//dumpWholeFile(file);
	
	char xbuffer[5];
	if (fread(xbuffer, sizeof(char), 4, file) != 4 || strcmp(xbuffer, "RIFF") != 0)
		throw "Not a WAV file";
	
	file_read_int32_le(xbuffer, file);
	if (fread(xbuffer, sizeof(char), 4, file) != 4 || strcmp(xbuffer, "WAVE") != 0)
		throw "Not a WAV file!";
	
	if (fread(xbuffer, sizeof(char), 4, file) != 4 || strcmp(xbuffer, "fmt ") != 0)
		throw "Invalid WAV file!";
	
	printf("char size: %lu", sizeof(char));
	
	errorNum = alGetError();
	
	GetALErrorString(errorNum);
	GetALCErrorString(errorNum);
	
	file_read_int32_le(xbuffer, file);
	short audioFormat = file_read_int16_le(xbuffer, file);
	short channels = file_read_int16_le(xbuffer, file);
	int sampleRate = file_read_int32_le(xbuffer, file);
	int byteRate = file_read_int32_le(xbuffer, file);
	file_read_int16_le(xbuffer, file);
	short bitsPerSample = file_read_int16_le(xbuffer, file);
	
	//if (audioFormat != 16) {
	//	short extraParams = file_read_int16_le(xbuffer, file);
	//	file_ignore_bytes(file, extraParams);
	//}
	
	bool atData = false;
	
	while (!atData) {
		if (fread(xbuffer, sizeof(char), 4, file) != 4 || strcmp(xbuffer, "data") != 0)
			printf("Discarding fluff\n");
		else
			atData = true;
			//throw "Invalid WAV file";
	}
	
	int dataChunkSize = file_read_int32_le(xbuffer, file)+4;
	unsigned char* bufferData = file_allocate_and_read_bytes(file, (size_t)dataChunkSize);
	
	printf("Error before alBufferData: %x\n", alGetError());
	
//	float duration = float(dataChunkSize)/byteRate;
	alBufferData(buffer, GetFormatFromInfo(channels, bitsPerSample), bufferData, dataChunkSize, sampleRate);
	//*dest = buffer;
	alSourcei(*dest, AL_BUFFER, buffer);
	errorNum = alGetError();
	free(bufferData);
	fclose(file);
}

void playHitSound() {
	alSourcePlay(hitSound);
	printf("Sound is meant to be playing");
}

void playSpinSound() {
	alSourcePlay(spinSound);
	printf("Sound is meant to be playing");
}

void playDeadSound() {
	alSourcePlay(deadSound);
	printf("Sound is meant to be playing");
}

void playScoreSound() {
	alSourcePlay(scoreSound);
	printf("Sound is meant to be playing");
}

void playMusic() {
	alSourcePlay(music);
	printf("Music is meant to be playing");
}

static void dumpWholeFile(FILE* file) {
	while (1) {
		printf("%c", fgetc(file));
	}
	printf("Done");
}

static inline ALenum GetFormatFromInfo(short channels, short bitsPerSample) {
	if (channels == 1) {
		if (bitsPerSample == 16) {
			return AL_FORMAT_MONO16;
		}
		return AL_FORMAT_MONO8;
	}
	if (bitsPerSample == 16) {
		return AL_FORMAT_STEREO16;
	}
	return AL_FORMAT_STEREO8;
}

static void file_ignore_bytes(FILE* file, short bytes) {
	while (bytes > 0) {
		printf("%c", (int)fgetc(file));
		bytes -= 1;
	}
}

static unsigned char* file_allocate_and_read_bytes(FILE* file, size_t chunkSize) {
	unsigned char* bytes = (unsigned char*)malloc(chunkSize);
	size_t bytesRead = fread(bytes, 1, chunkSize, file);
	printf("bytes read: %i\n", bytesRead);
	printf("Contents: ");
	for (int i=0; i<sizeof(*bytes); i++) {
		printf("%c", bytes[i]);
	}
	printf("\n");
	return bytes;
}

static unsigned int file_read_int32_le(char* buffer, FILE* file) {
	fread(buffer, 1, 4, file);
	printf("Buffer contents: ");
	for (int i=0; i<sizeof(buffer)/sizeof(char); i++) {
		printf("%c", (char)buffer[i]);
	}
	printf("\n");
	unsigned int val = *(unsigned int*)buffer;
	return CFSwapInt32LittleToHost(val);
}

static short file_read_int16_le(char* buffer, FILE* file) {
	fread(buffer, 1, 2, file);
	printf("Buffer contents: ");
	for (int i=0; i<sizeof(buffer)/sizeof(char); i++) {
		printf("%c", (char)buffer[i]);
	}
	printf("\n");
	unsigned int val = *(unsigned int*)buffer;
	return CFSwapInt32LittleToHost(val);	
}

template <typename T> T byte_reverse(T in) {
	T out;
	char* in_c = reinterpret_cast<char *> (&in);
	char* out_c = reinterpret_cast<char *> (&out);
	std::reverse_copy(in_c, in_c+sizeof(T), out_c);
	return out;
}

void muteMusic() {
	alSourcef(music, AL_GAIN, 0.0);
}

void unmuteMusic() {
	alSourcef(music, AL_GAIN, 0.4);
}

void GetALErrorString(ALenum err) {
	switch(err) {
		case AL_NO_ERROR:
		   printf("AL_NO_ERROR\n");
		   break;
		   
		case AL_INVALID_NAME:
		   printf("AL_INVALID_NAME\n");
		   break;
		   
		case AL_INVALID_ENUM:
		   printf("AL_INVALID_ENUM\n");
		   break;
		   
		case AL_INVALID_VALUE:
		   printf("AL_INVALID_VALUE\n");
		   break;
		   
		case AL_INVALID_OPERATION:
		   printf("AL_INVALID_OPERATION\n");
		   break;
		   
		case AL_OUT_OF_MEMORY:
		   printf("AL_OUT_OF_MEMORY\n");
		   break;
		default:
			printf("Unknown error\n");
	};
}

void GetALCErrorString(ALenum err) {
    switch(err)
    {
        case ALC_NO_ERROR:
            printf("AL_NO_ERROR\n");
			break;
			
        case ALC_INVALID_DEVICE:
            printf("ALC_INVALID_DEVICE\n");
			break;
			
        case ALC_INVALID_CONTEXT:
            printf("ALC_INVALID_CONTEXT\n");
			break;
			
        case ALC_INVALID_ENUM:
            printf("ALC_INVALID_ENUM\n");
			break;
			
        case ALC_INVALID_VALUE:
            printf("ALC_INVALID_VALUE\n");
			break;
			
        case ALC_OUT_OF_MEMORY:
            printf("ALC_OUT_OF_MEMORY\n");
			break;
		default:
			printf("Unknown error\n");
    };
}