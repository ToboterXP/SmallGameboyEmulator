/*
 * AudioInterface.h
 *
 *  Created on: 21.11.2019
 *      Author: Tobias
 */

#ifndef AUDIOINTERFACE_H_
#define AUDIOINTERFACE_H_

#include <SDL2/sdl.h>
#include <SDL2/SDL_mixer.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <math.h>

namespace audio {

const int CHANNEL_SQUARE_1 = 0;
const int CHANNEL_SQUARE_2 = 1;
const int CHANNEL_TRI = 2;
const int CHANNEL_NOISE = 3;

class AudioInterface {
protected:

	const uint16_t maxAmplitude = 10000;
	const uint16_t sampleSpeed = 22000;
	const uint8_t onVolume = 100;
public:
	int currentTimeStamp = 0;

	uint16_t lsfr = 0b101101101101;

	Mix_Chunk *square1 = NULL;
	Mix_Chunk *square2 = NULL;
	Mix_Chunk * tri = NULL;
	Mix_Chunk * noise = NULL;

	AudioInterface();
	virtual ~AudioInterface();
	void playSquareWave(int freq,int channel, int volume, int dutyCount, uint8_t * dutyValues);
	void playTriangleWave(int freq);
	void playNoise(int freq);
	void silenceChannel(int channel);
};
} /* namespace audio */

#endif /* AUDIOINTERFACE_H_ */
