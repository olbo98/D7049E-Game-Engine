#include "../src/AudioSystem/SoundDevice.h"
#include "../src/AudioSystem/SoundBuffer.h"
#include "../src/AudioSystem/SoundSource.h"
#include "../src/AudioSystem/MusicBuffer.h"

#include <iostream>


int main()
{
	std::cout << "Playing a sound...." << std::endl;
	SoundDevice* mySoundDevice = SoundDevice::getInstance();

	//Load a sound
	uint32_t sound1 = SoundBuffer::getInstance()->addSoundEffect("../Assets/audioFiles/res_spellsounds_spell.ogg");
	uint32_t sound2 = SoundBuffer::getInstance()->addSoundEffect("../Assets/audioFiles/burp2_x.wav");
	uint32_t sound3 = SoundBuffer::getInstance()->addSoundEffect("../Assets/audioFiles/VEHSkid_Tire squeal (ID 0500)_BSB.ogg");

	//Play the sound
	SoundSource speaker;

	MusicBuffer music("../Assets/audioFiles/countdown-30-seconds.wav");

	std::cout << "Playing music...." << std::endl;
	music.Play();
	
	while (true)
	{
		//speaker.Play(sound1);
		//speaker.Play(sound2);
		//speaker.Play(sound3);

		music.UpdateBufferStream();
	}
	
	std::cout << "File has played" << std::endl;
}
