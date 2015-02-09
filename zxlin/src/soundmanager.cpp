/***************************************************************************
                          soundmanager.cpp  -  description
                             -------------------
    begin                : ??? ??? 12 2005
    copyright            : (C) 2005 by vitaly
    email                : vitamin_caig@mail.ru
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "configure.h"
#include "soundmanager.h"

#include <alsa/pcm.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/soundcard.h>
#include "SDL/SDL.h"
#include "configure.h"

#include <sys/time.h>

SNDNoSound::SNDNoSound()
{
}

SNDNoSound::~SNDNoSound()
{
}

unsigned SNDNoSound::init(unsigned)
{

	return TRUE;
}

void SNDNoSound::syncWrite(const BYTE*, unsigned)
{
static DWORD prev = 0;
struct timeval timet;

	gettimeofday(&timet, NULL);
	timet.tv_usec += 1000000 * timet.tv_sec;
	prev += 20000;
	if (prev > timet.tv_usec)
		usleep(prev - timet.tv_usec);
	prev = timet.tv_usec;
}

//------------------

SNDOSS::SNDOSS()
{
	device = -1;
}

SNDOSS::~SNDOSS()
{
	if (device != -1) close(device);
}

unsigned SNDOSS::init(unsigned trying)
{
int tmp;

	try
	{
		device = open("/dev/dsp", O_WRONLY | O_NONBLOCK, 0);
		if (device == -1) throw "open(\"/dev/dsp\")";

		tmp = AFMT_S16_LE;
		if (ioctl(device, SNDCTL_DSP_SETFMT, &tmp) == -1) throw "SNDCTL_DSP_SETFMT";

		tmp = 16;   //samplesize
		ioctl(device, SNDCTL_DSP_SAMPLESIZE, &tmp);
		if (tmp != 16) throw "SNDCTL_DSP_SAMPLESIZE";

		tmp = 1;    //stereo
		if (ioctl(device, SNDCTL_DSP_STEREO, &tmp) == -1) throw "SNDCTL_DSP_STEREO";

		tmp = Configure::SNDFrequency;
		if (ioctl(device, SNDCTL_DSP_SPEED, &tmp) == -1) throw "SNDCTL_DSP_SPEED";

		tmp = 0x80008;
		if (Configure::SNDFrequency > 8000) tmp++;
		if (Configure::SNDFrequency > 16000) tmp++;
		if (Configure::SNDFrequency > 32000) tmp++;

		if (ioctl(device, SNDCTL_DSP_SETFRAGMENT, &tmp) < 0) throw "SNDCTL_DSP_SETFRAGMENT";
	}
	catch (const char* szMsg)
	{
		if (! trying) printf("OSS: %s failed\n", szMsg);
		if (device != -1)
		{
			close(device);
			device = -1;
		}
		return FALSE;
	}
	return TRUE;
}

void SNDOSS::syncWrite(const BYTE* pBuffer, unsigned samples)
{
audio_buf_info info;

	samples <<= 2;	//2 channels for 2 byte each
	if (! ioctl(device, SNDCTL_DSP_GETOSPACE, &info))
	{
			while (info.bytes < samples)
			{
                usleep(100);
                if (ioctl(device, SNDCTL_DSP_GETOSPACE, &info))
                    break;
			}
	}
    write(device, pBuffer, samples);
}

//---------------

SNDALSA::SNDALSA()
{
	pHandle = NULL;
	pParams = NULL;
	paused = bCanPause = FALSE;
}

SNDALSA::~SNDALSA()
{
	if (pHandle) snd_pcm_close(pHandle);
}

//TODO: put device + buffertime + periodtime to external config

unsigned SNDALSA::init(unsigned trying)
{
unsigned tmp;
int err;

	try
	{
		if ((err = snd_pcm_open(&pHandle, "hw:1,0", SND_PCM_STREAM_PLAYBACK, 0)) < 0) throw "open default";
		if ((err = snd_pcm_hw_params_malloc(&pParams)) < 0) throw "alloc params";
		if ((err = snd_pcm_hw_params_any(pHandle, pParams)) < 0) throw "init params";
		if ((err = snd_pcm_hw_params_set_access(pHandle, pParams, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) throw "set access type";
		if ((err = snd_pcm_hw_params_set_format(pHandle, pParams, SND_PCM_FORMAT_S16_LE)) < 0) throw "set sample format";
		tmp = Configure::SNDFrequency;
		if ((err = snd_pcm_hw_params_set_rate_near(pHandle, pParams, &tmp, 0)) < 0) throw "set frequency";
		if (tmp != Configure::SNDFrequency)
		{
			if (trying) throw "Unsupported frequency";
			printf("\n#Changing frequency to %i# ", Configure::SNDFrequency = tmp);
		}
		if ((err = snd_pcm_hw_params_set_channels(pHandle, pParams, 2)) < 0) throw "set channels";

		tmp = 100000;
		if ((err = snd_pcm_hw_params_set_buffer_time_near(pHandle, pParams, &tmp, 0)) < 0) throw "set buffer time";
		printf("\n#Sets %i usec buffer time# ", tmp);

		tmp = 1000;
		if ((err = snd_pcm_hw_params_set_period_time_near(pHandle, pParams, &tmp, 0)) < 0) throw "set period time";
		printf("\n#Sets %i usec period time# ", tmp);

		if ((err = snd_pcm_hw_params(pHandle, pParams)) < 0) throw "set params";
		bCanPause = snd_pcm_hw_params_can_pause(pParams);
		snd_pcm_hw_params_free(pParams);
		pParams = NULL;
		if ((err = snd_pcm_prepare(pHandle)) < 0) throw "playback prepare";
	}
	catch (const char* szMsg)
	{
		if (! trying) printf("ALSA: %s failed (%s)\n", szMsg, snd_strerror(err));
		if (pHandle) snd_pcm_close(pHandle);
		pHandle = NULL;
		if (pParams) snd_pcm_hw_params_free(pParams);
		pParams = NULL;
	}
	return TRUE;
}

void SNDALSA::syncWrite(const BYTE* pBuffer, unsigned samples)
{
	if (paused) return;
// recover after pause
	if (snd_pcm_writei(pHandle, pBuffer, samples) != samples)
		snd_pcm_prepare(pHandle);
}

void SNDALSA::pause(unsigned startstop)
{
	if (startstop)
		paused = TRUE;

	if (bCanPause)
		snd_pcm_pause(pHandle, startstop);
	else
		if (startstop)
			snd_pcm_drop(pHandle);

	if (! startstop)
		paused = FALSE;
}


#define MAX_FREQUENCY 96000

// ctor. initializing sound device for writing
SoundManager::SoundManager()
{
#define SND_DEVICES 3
const char* sndDevses[SND_DEVICES] = {"none", "OSS", "ALSA"};
int tmp = 0;

#ifdef _DEBUG_
    printf("SoundManager\n");
#endif
    pBuffer = NULL;
    lastTicks = 0;
    lastFrm = 0;

	int dev;
	int testing = FALSE;
	for (dev = 0; dev < SND_DEVICES && strcmp(sndDevses[dev], Configure::SNDDevice); dev++);

	if (dev == SND_DEVICES)	//auto
	{
		testing = TRUE;
		dev--;
	}

	do
	{
		switch (dev)
		{
		case 1:
			pOutput = new SNDOSS;
			break;
		case 2:
			pOutput = new SNDALSA;
			break;
		default:
			pOutput = new SNDNoSound;
			break;
		}

		if (testing && dev)
			printf("Trying %s: ", pOutput->name());
		if (! pOutput->init(testing))
		{
			if (! testing)
			{
				printf("Cannot initialize sound device %s, sound disabled\n", pOutput->name());
				dev = 0;
			}
			else
			{
				printf("failed!\n");
				dev--;
			}
			delete pOutput;
		}
		else
			break;
	}
	while (1);

	printf("Ok!\n");
	if (dev)	//not "none"
	{
		tmp = MAX_FREQUENCY * 2 * 16 / 400 + 128;
		pBuffer = new BYTE[tmp];
		tmp >>= 2;
		while (tmp) ((DWORD*)pBuffer)[--tmp] = 0x80008000;
	}
}

SoundManager::~SoundManager()
{
	delete pOutput;
    delete[] pBuffer;
#ifdef _DEBUG_
    printf("~SoundManager\n");
#endif
}

void SoundManager::startFrame()
{
static unsigned samples = Configure::SNDFrequency / 50;//* 2 * 16 / 400;

//calculate ticks per impulse
    ticksPerImp = Configure::ULATicksPerFrame * 50 / Configure::SNDFrequency + 1;

	pOutput->syncWrite(pBuffer, samples);

    lastTicks -= Configure::ULATicksPerFrame;
}




void SoundManager::renderUntil(unsigned ticks)
{
    if (pBuffer == NULL) return;
    if ((int(ticks) - int(lastTicks)) < int(ticksPerImp)) return;  // not enough time to render value
    long long frq = int(Configure::SNDFrequency);
    unsigned to = (frq * ticks / (Configure::ULATicksPerFrame * 50)) % (frq / 50);
//    if (lastFrm == to) return;
    int left = 0, right = 0;
    int leftval = 0, rightval = 0;
    QPtrListIterator<SoundDevice> iDev(list);
    // mixing all devices
	int ctr = 0;
    while (SoundDevice* pDev = iDev.current())
    {
        ++iDev;
        pDev->getLevel(&left, &right, ticks - lastTicks);
        leftval += left;
        rightval += right;
		ctr++;
    }
	leftval /= ctr;
	rightval /= ctr;
    if (leftval < -32768) leftval = -32768;
    if (leftval > 32767) leftval = 32767;
    if (rightval < -32768) rightval = -32768;
    if (rightval > 32767) rightval = 32767;
    leftval += 32768;
    rightval += 32768;
    leftval = leftval + (rightval << 16);
    // rendering
    do
    {
        ((DWORD*)pBuffer)[lastFrm] = leftval;
        lastFrm = (++lastFrm) % (Configure::SNDFrequency / 50);
    }
    while (lastFrm != to);
    lastTicks = ticks;
}

// sequentally render all chunks
void SoundManager::retrace()
{
    if (pBuffer == NULL) return;
    while (lastTicks < Configure::ULATicksPerFrame)
        renderUntil(lastTicks + ticksPerImp);
}

void SoundManager::pause(unsigned startstop)
{
	pOutput->pause(startstop);
}

void SoundManager::addDevice(SoundDevice* dev)
{
    list.append(dev);
}

unsigned SoundManager::deleteDevice(SoundDevice* dev)
{
	return list.removeRef(dev);
}
