/***************************************************************************
                          types.h  -  description
                             -------------------
    begin                : ����12 2005
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

#ifndef TYPES
#define TYPES

#define MAX_VERSION 0.1

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned long long QWORD;
typedef char TEXT;

#define COLOR_MATRIX 0x0f
#define COLOR_FOCUSED 0x9f
#define COLOR_SELECTED 0xc0
#define COLOR_EDIT 0xe0
#define COLOR_CURSOR 0x0e
#define COLOR_BREAKPOINT 0xaf

#define DISASM_LINES 10

#define CONTEXT_X 0
#define CONTEXT_Y 0

#define DISASM_X CONTEXT_X
#define DISASM_Y 88

#define DUMP_X CONTEXT_X
#define DUMP_Y ((DISASM_LINES + 6) * 16)

// fixed!!!!!!
#define SCREEN_X 320
#define SCREEN_Y 0

#define AY_X 280
#define AY_Y 8

#define MEMORY_X 0
#define MEMORY_Y (DUMP_Y + 9 * 16 + 8)

#define BETA_X (DUMP_X + 70 * 8)
#define BETA_Y DUMP_Y


#if (!defined(NULL))
#define NULL (void*)0
#endif

#define TRUE 1
#define FALSE 0

#define MAX_PATH_LEN 512
#define MAX_DESCRIPTION_LEN 512

#define DOUBLESIZE

#if !defined(DOUBLESIZE)
#define W_WIDTH 320
#define W_HEIGHT 240
#else
#define W_WIDTH 640
#define W_HEIGHT 480
#endif

#define MAXPATHLEN 4096

//memory types
enum EMemType
{
    MEM_PENT128,
    MEM_PENT512,

    MEM_SCORP256,
    MEM_ATM512,
    MEM_PROFI1024,
    MEM_SCORP1024,

    MEMTYPES
};

//superclass reference
class Zxlin;
extern Zxlin* ZXLin;


#endif
