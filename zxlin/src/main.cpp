/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : ����12 21:05:58 MSK 2005
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

#include "zxlin.h"
#include <qapplication.h>

Zxlin* ZXLin = NULL;

int main(int argc, char *argv[])
{
#ifdef _DEBUG_
    chdir("/home/vitamin/prog/zxlin/result");
#endif
    Configure::loadIni("zxlin.ini");

//parse command line
int parpos = 1;
    while (parpos < argc)
    {
        if (! strcmp(argv[parpos], "--help") || ! strcmp(argv[parpos], "-?"))
        {
            printf("ZXLin version %s\n"
                   "(C) Vitamin/CAIG/2001\n\n"
					"Build from:" __DATE__ " " __TIME__ "\n"
                   "Usage:\n"
                   "%s [parameters] [file]\n\n"
                   "Parameters:\n"
                   "-? --help -   this page\n"
                   "-c --configure <file.ini> - use <file.ini> as a configure file (instead of zxlin.ini)\n"
                   "-f --fullscreen - run in fullscreen\n"
                   "\n", VERSION, *argv
                   );
            return 0;
        }
        if (! strcmp(argv[parpos], "-c") || ! strcmp(argv[parpos], "--configure"))
        {
            Configure::loadIni(argv[parpos + 1]);
            parpos += 2;
            continue;
        }
        if (! strcmp(argv[parpos], "-f") || ! strcmp(argv[parpos], "--fullscreen"))
        {
            Configure::VIDFullScreen = TRUE;
            parpos++;
            continue;
        }
        if (parpos == argc - 1)
        {
            strcpy(Configure::VARAutoLoad, argv[parpos]);
            break;
        }
    }

    QApplication app(argc, argv, TRUE);
    ZXLin = new Zxlin();
    ZXLin->run();
  //never get here!!!
}
