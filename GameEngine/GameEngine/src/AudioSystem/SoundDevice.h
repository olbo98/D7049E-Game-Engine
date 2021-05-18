#pragma once
#include <AL/alc.h>
#include <AL/al.h>


/* Singleton that initialises the audio */
class SoundDevice
{
public:
	static SoundDevice* getInstance();
private:
	SoundDevice();
	~SoundDevice();


	ALCdevice* p_ALCDevice;
	ALCcontext* p_ALCContext;

	
};

