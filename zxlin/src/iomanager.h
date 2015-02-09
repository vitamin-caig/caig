/***************************************************************************
                          iomanager.h  -  description
                             -------------------
    begin                : ??? ??? 19 2005
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

#ifndef IOMANAGER_H
#define IOMANAGER_H


/**
  *@author vitaly
  */

#include "types.h"
#include "device.h"
#include <qptrlist.h>

// input-output manager for computer

class IOManager// : public Device
{
public:
    IOManager();
    virtual ~IOManager();

    virtual void reset();
    virtual unsigned inByte(WORD port);
    virtual void outByte(WORD port, BYTE data);
    virtual void showState(unsigned full);

	void addDevice(Device* pDevice, unsigned buffered = TRUE);
	unsigned deleteDevice(Device* pDevice, unsigned buffered = TRUE);
private:
    QPtrList<Device> unbuff;
	QPtrList<Device> buff;
};

#endif
