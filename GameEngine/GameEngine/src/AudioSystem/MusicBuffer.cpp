#include "MusicBuffer.h"
#include <cstddef>
#include <AL\alext.h>
#include <malloc.h>
#include <iostream>


MusicBuffer::MusicBuffer(const char* filename)
{
	/* Generates the sources and buffers */
	alGenSources(1, &Source);
	alSourcef(Source, AL_GAIN, p_Gain);
	alGenBuffers(NUM_BUFFERS, p_Buffers);

	std::size_t frame_size;

	p_SndFile = sf_open(filename, SFM_READ, &p_Sfinfo);
	if (!p_SndFile)
	{
		throw("could not open provided music file -- check path");
	}

	/* Get the sound format, and figure out the OpenAL format */
	if (p_Sfinfo.channels == 1)
		p_Format = AL_FORMAT_MONO16;
	else if (p_Sfinfo.channels == 2)
		p_Format = AL_FORMAT_STEREO16;
	else if (p_Sfinfo.channels == 3)
	{
		if (sf_command(p_SndFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
			p_Format = AL_FORMAT_BFORMAT2D_16;
	}
	else if (p_Sfinfo.channels == 4)
	{
		if (sf_command(p_SndFile, SFC_WAVEX_GET_AMBISONIC, NULL, 0) == SF_AMBISONIC_B_FORMAT)
			p_Format = AL_FORMAT_BFORMAT3D_16;
	}
	if (!p_Format)
	{
		sf_close(p_SndFile);
		p_SndFile = NULL;
		throw("Unsupported channel count from file");
	}

	/* For loading the frame size and allocates the memory so that it points to the correct data */
	frame_size = ((size_t)BUFFER_SAMPLES * (size_t)p_Sfinfo.channels) * sizeof(short);
	p_Membuf = static_cast<short*>(malloc(frame_size));

}

MusicBuffer::~MusicBuffer()
{
	alDeleteSources(1, &Source);

	if (p_SndFile)
		sf_close(p_SndFile);

	p_SndFile = nullptr;

	free(p_Membuf);

	alDeleteBuffers(NUM_BUFFERS, p_Buffers);

}

void MusicBuffer::Play()
{
	ALsizei i;

	// clear any al errors
	alGetError();

	/* Rewind the source position and clear the buffer queue */
	alSourceRewind(Source);
	alSourcei(Source, AL_BUFFER, 0);

	/* Fill the buffer queue */
	for (i = 0; i < NUM_BUFFERS; i++)
	{
		/* Get some data to give it to the buffer */
		sf_count_t slen = sf_readf_short(p_SndFile, p_Membuf, BUFFER_SAMPLES);
		if (slen < 1) break;

		slen *= p_Sfinfo.channels * (sf_count_t)sizeof(short);
		alBufferData(p_Buffers[i], p_Format, p_Membuf, (ALsizei)slen, p_Sfinfo.samplerate);
	}
	if (alGetError() != AL_NO_ERROR)
	{
		throw("Error buffering for playback");
	}

	/* Now queue and start playback! */
	alSourceQueueBuffers(Source, i, p_Buffers);
	alSourcePlay(Source);
	if (alGetError() != AL_NO_ERROR)
	{
		throw("Error starting playback");
	}

	ALint state = AL_PLAYING;
	while (state == AL_PLAYING && alGetError() == AL_NO_ERROR)
	{
		std::cout << "currently playing sound\n";

		alGetSourcei(Source, AL_SOURCE_STATE, &state);
	}
	
	
}

void MusicBuffer::UpdateBufferStream()
{
	ALint processed, state;

	// clear error 
	alGetError();
	/* Get relevant source info as checking what state and what data has been processed */
	alGetSourcei(Source, AL_SOURCE_STATE, &state);
	alGetSourcei(Source, AL_BUFFERS_PROCESSED, &processed);
	if (alGetError() != AL_NO_ERROR)
	{
		throw("error checking music source state");
	}

	/* Unqueue and handle each processed buffer */
	while (processed > 0)
	{
		ALuint bufid;
		sf_count_t slen;

		alSourceUnqueueBuffers(Source, 1, &bufid);
		processed--;

		/* Read the next chunk of data, refill the buffer, and queue it
		 * back on the source */
		slen = sf_readf_short(p_SndFile, p_Membuf, BUFFER_SAMPLES);
		if (slen > 0)
		{
			slen *= p_Sfinfo.channels * (sf_count_t)sizeof(short);
			alBufferData(bufid, p_Format, p_Membuf, (ALsizei)slen,
				p_Sfinfo.samplerate);
			alSourceQueueBuffers(Source, 1, &bufid);
		}
		if (alGetError() != AL_NO_ERROR)
		{
			throw("error buffering music data");
		}
	}

	/* Make sure the source hasn't underrun */
	if (state != AL_PLAYING && state != AL_PAUSED)
	{
		ALint queued;

		/* If no buffers are queued, playback is finished */
		alGetSourcei(Source, AL_BUFFERS_QUEUED, &queued);
		if (queued == 0)
			return;

		alSourcePlay(Source);
		if (alGetError() != AL_NO_ERROR)
		{
			throw("error restarting music playback");
		}
	}

}