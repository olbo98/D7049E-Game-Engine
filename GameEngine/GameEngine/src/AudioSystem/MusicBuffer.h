#pragma once
#include <AL\al.h>
#include <sndfile.h>

/* A music buffer class to play longer sequences of music */
class MusicBuffer
{
public:
	MusicBuffer(const char* filename);
	~MusicBuffer();

	/* Playing the music by filling and generating the buffers */
	void Play();
	
	/* Called every frame to be able to continue playing and go through more data. You basically rebuffer anything that is done playing */
	void UpdateBufferStream();

	//ALint getSource();

	
private:
	ALuint Source;
	static const int BUFFER_SAMPLES = 8192; //8kb in every buffer
	static const int NUM_BUFFERS = 4; //Loops through these buffers to play the entire music sequence
	ALuint p_Buffers[NUM_BUFFERS];

	SNDFILE* p_SndFile;
	SF_INFO p_Sfinfo;
	short* p_Membuf;
	ALenum p_Format; 

	MusicBuffer() = delete;
};
