/***************************************************************************
                          soundmanager.h  -  description
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

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <alsa/asoundlib.h>
#include "iomanager.h"

/**
  *@author vitaly
  */


// sound outputter interface
class SoundOutput
{
public:
	virtual ~SoundOutput() {}
	virtual unsigned init(unsigned trying) = 0;
	virtual void syncWrite(const BYTE* pBuffer, unsigned samples) = 0;
	virtual void pause(unsigned startstop) = 0;
	virtual const char* name() = 0;
};

//no sound -> only syncro
class SNDNoSound : public SoundOutput
{
public:
	SNDNoSound();
	virtual ~SNDNoSound();

	virtual unsigned init(unsigned trying);
	virtual void syncWrite(const BYTE* pBuffer, unsigned samples);
	virtual void pause(unsigned) {};
	virtual const char* name() {return "none";}
};

// OSS module
class SNDOSS : public SoundOutput
{
public:
	SNDOSS();
	virtual ~SNDOSS();

	virtual unsigned init(unsigned trying);
	virtual void syncWrite(const BYTE* pBuffer, unsigned samples);
	virtual void pause(unsigned) {};
	virtual const char* name() {return "OSS";}
private:
	int device;
};

// ALSA module
class SNDALSA : public SoundOutput
{
public:
	SNDALSA();
	virtual ~SNDALSA();

	virtual unsigned init(unsigned trying);
	virtual void syncWrite(const BYTE* pBuffer, unsigned samples);
	virtual void pause(unsigned startstop);
	virtual const char* name() {return "ALSA";}
private:
	snd_pcm_t* pHandle;
	snd_pcm_hw_params_t* pParams;
	unsigned paused;
	unsigned bCanPause;
};

// sound devices manager for computer

class SoundManager : public TimetricDevice
{
public:
    SoundManager();
    virtual ~SoundManager();

    virtual void startFrame();
    virtual void renderUntil(unsigned cntr);
    virtual void retrace();

	void pause(unsigned startstop);
    void addDevice(SoundDevice* dev);
	unsigned deleteDevice(SoundDevice* dev);
private:
    unsigned lastTicks;
    unsigned lastFrm;
    unsigned ticksPerImp;
    BYTE* pBuffer;
	SoundOutput* pOutput;
    QPtrList<SoundDevice> list;
};

#endif
