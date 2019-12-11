/*
 * AudioInterface.cpp
 *
 *  Created on: 21.11.2019
 *      Author: Tobias
 */

#include <audio/AudioInterface.h>

namespace audio {

AudioInterface::AudioInterface() {
	Mix_Init(0);

	Mix_OpenAudio(sampleSpeed,AUDIO_U16,1,1024);

	Mix_AllocateChannels(4);
}

AudioInterface::~AudioInterface() {

}

void AudioInterface::playSquareWave(int freq,int channel, int volume, int dutyCount, uint8_t * dutyValues) {
	Mix_Chunk **chunk = channel == CHANNEL_SQUARE_1 ? &square1:&square2;
	if (chunk) Mix_FreeChunk(*chunk);

	int sampleFreq = 2*sampleSpeed/freq;

	Uint16 * data = new Uint16[dutyCount*((int)sampleFreq)];
	for (int h=0;h<dutyCount;h++) {
		int fallingEdge = (sampleFreq*dutyValues[h])/8;
		for (int i=h*sampleFreq;i<(h+1)*sampleFreq;i++) {
			data[i] = i%sampleFreq<fallingEdge ? (maxAmplitude*volume)/7 : 0;
		}
	}

	*chunk = Mix_QuickLoad_RAW((uint8_t*)data,dutyCount*sampleFreq*sizeof(Uint16));
	Mix_Volume(channel,onVolume);
	Mix_PlayChannel(channel,*chunk,-1);
}

void AudioInterface::silenceChannel(int channel) {
	Mix_Volume(channel,0);
}

void AudioInterface::playTriangleWave(int freq) {
	if (tri) Mix_FreeChunk(tri);

	int sampleFreq = 2*sampleSpeed/freq;

	Uint16 * data = new Uint16[(int)sampleFreq];
	for (int i=0;i<sampleFreq;i++) {
		data[i] = i%sampleFreq<sampleFreq/2 ? (i*maxAmplitude)/(sampleFreq/2) : ((sampleFreq-i)*maxAmplitude)/(sampleFreq/2);
	}

	tri = Mix_QuickLoad_RAW((uint8_t*)data,sampleFreq*2);
	Mix_Volume(CHANNEL_TRI,onVolume);
	Mix_PlayChannel(CHANNEL_TRI,tri,-1);
}

void AudioInterface::playNoise(int freq) {
	if (noise) Mix_FreeChunk(noise);

	int sampleFreq = 2*sampleSpeed/freq;

	Uint16 * data = new Uint16[sampleFreq*50];
	for (int j=0;j<100;j++) {
		uint8_t new_lsfr_bit = (lsfr&1)^((lsfr>>1)&1);
		lsfr >>=1;
		lsfr |= new_lsfr_bit<<15;
		for (int i=j*sampleFreq;i<(j+1)*sampleFreq;i++) {
			data[i] = new_lsfr_bit * maxAmplitude;
		}
	}

	noise = Mix_QuickLoad_RAW((uint8_t*)data,sampleFreq*100);
	Mix_Volume(CHANNEL_NOISE,onVolume);
	Mix_PlayChannel(CHANNEL_NOISE,noise,-1);
}


} /* namespace audio */
