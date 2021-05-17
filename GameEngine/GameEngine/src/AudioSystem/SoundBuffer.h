#pragma once
#include "AL\al.h"
#include <vector>

/* Soundbuffer (Singleton) holds the samples of audio that the sources are going to be playing for the listeners */
class SoundBuffer
{
public:
	static SoundBuffer* getInstance();

	ALuint addSoundEffect(const char* filename);
	bool removeSoundEffect(const ALuint& buffer);

private:
	SoundBuffer();
	~SoundBuffer();

	//Uploads and removes the soundeffects into and from this vector
	std::vector<ALuint> p_SoundEffectBuffers;
};

