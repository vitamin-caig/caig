// alasmview.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "listplug.h"
#include "stdio.h"

#define parsefunction ""
//"force | ((EXT=\"H\" | EXT=\"$H!\") & [40]=243 & [41]=118 & [42]=199) | (EXT=\"$H\" & [57]=243 & [58]=118 & [59]=199)"

//directive
#define D(a) "\x1" #a
//mnemonic
#define M(a) "\x2" #a
#define OPERAND 3
//operand
#define O(a) "\x3" #a
//comment
#define COMMENT 4
//string
#define STRING 5
//number
#define NUMBER 6
//default color
#define DEFAULT 7

//bbggrr
struct STYLE
{
	DWORD color;
	unsigned bold;
	unsigned italic;
};

HINSTANCE hInst = 0;
HMODULE hmFLibHandle = 0;
int iLastLoadTime = 0;
STYLE styles[DEFAULT] = {{0xff0000, 0, 0}, {0xff, 0, 0}, {0x4040c0, 0, 0}, {0xc000, 0, 0},
							{0xff00ff, 0, 0}, {0xc000c0, 0, 0}, {0xc0c0c0, 0, 0}};
DWORD bgCol;
DWORD fntSize;
int bColored = TRUE;
char inifilename[MAX_PATH];
const char inifile[] = "inX.cfg";
const char appname[] = "alasmview";

#if (0)
FILE* filelog;
#define DEBUGMSG(a, b) fprintf(filelog, a, b);\
						fflush(filelog);
#define DEBUGSTART filelog = fopen("alasmview.log", "wt");
#define DEBUGEND fclose(filelog);
#else
#define DEBUGMSG(a, b)
#define DEBUGSTART
#define DEBUGEND
#endif 

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
const char* sectnames[DEFAULT] = {"directive", "mnemonic", "operand", "comment", "string", "number", "default"};
LPTSTR pCmd;
char szTmp[256];
unsigned i;

    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			DEBUGSTART
			DEBUGMSG("Attaching to process %p\n", hModule)
			hInst=(HINSTANCE)hModule;
			pCmd = GetCommandLine();
			strcpy(inifilename, pCmd + (*pCmd == '\"'));
			pCmd = strrchr(inifilename, '\\') + 1;
			strcpy(pCmd, inifile);
			//loading
			bgCol = GetPrivateProfileInt(appname, "background", 0xffffff, inifilename);
			fntSize = GetPrivateProfileInt(appname, "fontsize", 16, inifilename);
			bColored = GetPrivateProfileInt(appname, "colored", FALSE, inifilename);
			for (i = 0; i < DEFAULT; i++)
			{
				GetPrivateProfileString(appname, sectnames[i], NULL, szTmp, 255, inifilename);
				if (*szTmp)
				{
					//color,bold,italic
					sscanf(szTmp, "%x,%i,%i", &(styles[i].color), &(styles[i].bold), &(styles[i].italic));
				}
			}
			break;
		case DLL_PROCESS_DETACH:
			DEBUGMSG("Detach from process %p", hModule)
			DEBUGEND
			if (hmFLibHandle)
				FreeLibrary(hmFLibHandle);
			hmFLibHandle=NULL;
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
    }
    return TRUE;
}

void PutToken(BYTE bTok, char* szTo, int* pInd, int bIsTok)
{
// from 0x80
static const char* szTokens[] = {
D(INCLUDE), D(INCBIN), D(MACRO), D(LOCAL), M(RLCA), M(RRCA), M(HALT), M(CALL),
M(PUSH), M(RETN), M(RETI), M(DJNZ), M(OUTI), M(OUTD), M(LDIR), M(CPIR),
M(INIR), M(OTIR), M(LDDR), M(CPDR), M(INDR), M(OTDR), D(DD), D(DEFB),
D(DEFW), D(DEFS), D(DISP), D(ENDM), D(EDUP), D(ENDL), D(MAIN), D(ELSE),
D(DISPLAY), M(EXA), D(DB), D(DW), D(DS), M(NOP), M(INC), M(DEC),
M(RLA), M(RRA), M(DAA), M(CPL), M(SCF), M(CCF), M(ADD), M(ADC),
M(SUB), M(SBC), M(AND), M(XOR), M(RET), M(POP), M(RST), M(EXX),
M(RLC), M(RRC), M(SLA), M(SRA), M(SLI), M(SRL), M(BIT), M(RES),
M(SET), M(OUT), M(NEG), M(RRD), M(RLD), M(LDI), M(CPI), M(INI),
M(LDD), M(CPD), M(IND), D(ORG), D(EQU), D(ENT), M(INF), D(DUP),
D(IFN), D(REPEAT), D(UNTIL), D(IF), M(LD), M(JR), M(JP), M(OR),
M(CP), M(EX), M(DI), M(EI), M(IN), M(RL), M(RR), M(IM),
D(ENDIF), M(EXD), M(JNZ), M(JZ), M(JNC), M(JC), D(RUN)
//till 0xe6 include
};

// from 0x9f
static const char* szOperands[92] = {
O((BC)),
O((DE)), O((HL)), O((SP)), O((IX)), O((IY)), "\xa5", "\xa6", "\xa7",
"\xa8", "\xa9", "\xaa", "\xab", "\xac", "\xad", "\xae", "\xaf",
"\xb0", "\xb1", "\xb2", "\xb3", "\xb4", "\xb5", "\xb6", "\xb7",
"\xb8", "\xb9", "\xba", "\xbb", "\xbc", "\xbd", "\xbe", "\xbf",
"\xc0", "\xc1", "\xc2", "\xc3", "\xc4", "\xc5", "\xc6", "\xc7",
"\xc8", "\xc9", "\xca", "\xcb", "\xcc", "\xcd", "\xce", "\xcf",
O((C)),  O(\x28IX),  O(\x28IY),  O(AF\x27),  "\xd4", "\xd5", "\xd6", "\xd7",
"\xd8", "\xd9", "\xda", "\xdb", "\xdc", "\xdd", "\xde", "\xdf",
O(BC),   O(DE),   O(HL),   O(AF),   O(IX),   O(IY),   O(SP),   O(NZ),
O(NC),   O(PO),   O(PE),   O(HX),   O(LX),   O(HY),   O(LY),   O(B),
O(C),    O(D),    O(E),    O(H),    O(L),    O(A),    O(P),    O(M),
O(Z),    O(R),	O(I)
};

char* pToka = !bIsTok ? (char*)szOperands[bTok - 0x9f] : (char*)szTokens[bTok - 0x80];

	if (!bColored && *pToka < ' ')pToka++;
	while (*pToka) szTo[(*pInd)++] = *pToka++;
}

bool GetStr(BYTE* pFrm, int* pPos, char* pTo, int* pTPos, BYTE* pLen, bool bCop)
{
	while (--(*pLen))
	{
		BYTE bDat= pFrm[(*pPos)++];
		if (bDat >= 0x20 && bDat != 0xff)
		{
			pTo[(*pTPos)++] = bDat;
			if ((! bCop) && bDat == 0x22) return true;
		}
	}
	return false;
}

void DoString(BYTE* pData, char* szDest)
{
BYTE bDat = 0;
int iPos = 0;
enum
{
	MDUMMY,
	MARRAY,
	MBINNUM,
	MDECNUM,
	MHEXNUM,
} state = MDUMMY;
int wasToken = TRUE;
int firstToken = TRUE;
int bLen = *pData++;


int lastcolor = DEFAULT;

	if (bColored) *szDest = lastcolor;
	if (bLen)
	{
		while (--bLen > 0)
		{
			wasToken = !wasToken;
			bDat = *pData++;
			if (bDat == 0xff)	//dummy
			{
				wasToken = FALSE;
				continue;
			}
			//test numbers
			if (state == MDUMMY && (bDat == '+' || bDat == '-' || bDat == '%' || bDat == '#' || (bDat >= '0' && bDat <= '9')))
			{
				BYTE* pTData = pData;//second symbol
				int bTLen = bLen;
				if (bDat == '-' || bDat == '+') bDat = *pData, pTData++, bTLen--;
				if (bDat == '%')
					state = MBINNUM;
				else if (bDat == '#')
						state = MHEXNUM;
					else if (bDat >= '0' && bDat <= '9')
							state = MDECNUM;
				if (state != MDUMMY)
				{
					while (--bTLen &&
						   ((state >= MBINNUM && *pTData >= '0' && *pTData <= '1') ||
							(state >= MDECNUM && *pTData >= '2' && *pTData <= '9') ||
							(state == MHEXNUM && *pTData >= 'A' && *pTData <= 'F'))) pTData++;
					if (!bTLen || strchr("\x1\x2\x3\x4\x5\x6\x7\x8\x9\xa\xb\xc\xd\xe\xf +-*/&|!><)}~;,?=\xff", *pTData))
					{
						if (bColored && lastcolor != NUMBER)
							szDest[iPos++] = NUMBER;
						pData--;
						while (pData != pTData) bLen--, szDest[iPos++] = *pData++;
						bLen++;
						if (bColored)
							szDest[iPos] = lastcolor;
					}
					
					state = MDUMMY;
					continue;
				}
				else
				{
					bDat = pData[-1];
					if (bColored)
						szDest[iPos] = lastcolor;
				}
			}
			//test comments or russian
			if (bDat == ';' || bDat == 0x10)
			{
				if (bDat == ';')
				{
					if (bColored)
						szDest[iPos++] = COMMENT;
					szDest[iPos++] = ';';
				}
				else
					if (bColored)
						szDest[iPos++] = DEFAULT;
				while (--bLen && *pData != 0xff) szDest[iPos++] = *pData++;
				break;//till the end of line
			}
			
			//test strings
			if (bDat == '\"')
			{
				if (bColored)
					szDest[iPos++] = STRING;
				szDest[iPos++] = '\"';
				while (--bLen && *pData != '\"' && *pData != 0xff) szDest[iPos++] = *pData++;
				if (! bLen || *pData == 0xff)
				{
					if (bColored)
						szDest[iPos] = lastcolor;
					break;
				}
				szDest[iPos++] = *pData++;
				if (bColored)
					szDest[iPos] = lastcolor;
				continue;
			}
			//tabulation
			if (bDat < 0x10)
			{
				while (bDat--) szDest[iPos++] = 32;
				if (bColored)
					lastcolor = szDest[iPos] = DEFAULT;
				state = MDUMMY;
				continue;
			}
			// tokens
			if (bDat >= 128)
			{
				while (iPos < 8 && ! wasToken) szDest[iPos++] = 32;	//put needful spaces
				PutToken(bDat, szDest, &iPos, firstToken);
				if (firstToken)
				{
					firstToken = FALSE;
					szDest[iPos++] = ' ';
				}
				if (bColored)
					lastcolor = szDest[iPos] = OPERAND;
				state = MDUMMY;
				continue;
			}
			if (szDest[iPos] == DEFAULT || szDest[iPos] == OPERAND) szDest++;
			szDest[iPos++] = bDat;
			if ((bDat >= 'A' && bDat <= 'Z') ||
				(bDat >= 'a' && bDat <= 'z') ||
				(bDat >= '0' && bDat <= '9') ||
				bDat == '_')
				state = MARRAY;
			else
				state = MDUMMY;
			wasToken = TRUE;
		}
	}
	szDest[iPos] = '\n';
	szDest[iPos + 1] = 0;
}


char* ConvertData(BYTE* pSData, int iSize)
{
char* szRes = new char[1000000];
char* pString = new char[200];
int iRes = 0;

	
	BYTE* pData = pSData + 64;
	while (*pData && pData < pSData + iSize)
	{
		memset(pString, 0, 200);
		DoString(pData, pString);
		pData += *pData;
		OemToChar(pString, pString);
		int iStr = strlen(pString);
		memcpy(szRes + iRes, pString, iStr);
		szRes[iRes += iStr] = 0;
	}
	delete[] pString;
	
	return szRes;
}

DWORD CALLBACK putCallback(DWORD dwCookie, LPBYTE buff, LONG size, LONG FAR* pcb)
{
LPBYTE ptr = buff;
char** pSrc = (char**)dwCookie;
char* src = *pSrc;

	LONG datalen = strlen(src);
	if (datalen > size) datalen = size;
	memcpy(buff, src, datalen);
	src += *pcb = datalen;
	*pSrc = src;
	return 0;
}

char* ConvertToRTF(char* src)
{
BYTE* pSrc = (BYTE*)src;
char* dst = new char[1024 * 1024];
char* pDst = dst;

	pDst += sprintf(pDst, "{\\rtf1\\ansi\\ansicp1251\\deff0\\deflang1049"
						  "{\\fonttbl"
						  "{\\f0\\fmodern\\fprq1\\fcharset204{\\*\\fname Courier New;}Courier New CYR;}"
						  "{\\f1\\fnil\\fprq1\\fcharset0 Courier New CYR;}"
						  "}\n"	//fonttable
						  "{\\colortbl "
						  );
	for (int i = -1; i < DEFAULT; i++)
	{
		unsigned col = i == -1 ? bgCol : styles[i].color;
		pDst += sprintf(pDst, "\\red%i\\green%i\\blue%i;", col >> 16, (col & 0xff00) >> 8, col & 0xff);
	}
	pDst += sprintf(pDst, "}\n\\f1\\fs%i\\cf%i\n", fntSize, DEFAULT);
	int lastcol = -1;
	unsigned lastbold = 0;
	unsigned lastital = 0;
	int sym;
	do
	{
		sym = *pSrc++;
		switch (sym)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			if (styles[sym - 1].bold != lastbold)
			{
				lastbold = styles[sym - 1].bold;
				pDst += sprintf(pDst, "\\b%i", lastbold ? 1 : 0);
			}
			if (styles[sym - 1].italic != lastital)
			{
				lastital = styles[sym - 1].italic;
				pDst += sprintf(pDst, "\\i%i", lastital ? 1 : 0);
			}
			if (lastcol != sym)
				pDst += sprintf(pDst, "\\cf%i ", lastcol = sym);
			break;
			
		case '\n':
			pDst += sprintf(pDst, "\\line\n");
			break;

		case '{':
		case '}':
		case '\\':
			*pDst++ = '\\';
			*pDst++ = sym;
			break;
			
		case 0:
			*pDst++ = '}';
			*pDst++ = 0;

		default:
			if (sym >= 128)
				pDst += sprintf(pDst, "\\'%02x", sym);
			else
				*pDst++ = sym;
			break;
		}
	}
	while (sym);
	/*
	FILE* fil = fopen("text.rtf", "wb");
	fputs(dst, fil);
	fclose(fil);
	*/
	delete[] src;
	return dst;
}

HWND __stdcall ListLoad(HWND hwParentWin, char* szFileToLoad, int iShowFlags)
{
HWND hWnd = 0;
RECT rRect;
DWORD dwW2 = 0;
char* szStr = NULL;
BOOL bSucceed = false;

	DEBUGMSG("Checking %s\n", szFileToLoad)
	
	szStr = strrchr(szFileToLoad, '\\');
	if (! szStr)
	{
		DEBUGMSG("Cannot find \'\\\' symbol in path %s\n", szFileToLoad);
		return NULL;
	}
	szStr = strrchr(szStr, '.');
	if (!szStr)
	{
		DEBUGMSG("Extention not found in %s\n", szFileToLoad);
		return NULL;
	}
	
	DEBUGMSG("Loading %s\n", szFileToLoad);
	// Extension is supported -> load file
	HANDLE hFile = CreateFile(szFileToLoad, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
							FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		DEBUGMSG("Cannot load %s!!!\n", szFileToLoad);
		return NULL;
	}

	int iL = GetFileSize(hFile, NULL);
	if (iL > 16384 + 17)
	{
		DEBUGMSG("Wrong size: %i\n", iL);
		CloseHandle(hFile);
		return NULL;
	}

	BYTE* pData = new BYTE[iL];
	ReadFile(hFile, pData, iL, &dwW2, NULL);
	CloseHandle(hFile);

	if (szStr[1] == '$' && (*((DWORD*)(pData + 0x28 + 17)) == 0xddc776f3))
	{
		memcpy(szStr + 1, pData + 8, 3);
		iL = *((WORD*)(pData + 11));
		memcpy(pData, pData + 17, iL);
		DEBUGMSG("Found hobeta %8s\n", pData)
	}

	if (dwW2 < 0) dwW2 = 0;
	if (dwW2 > (DWORD)iL) dwW2 = iL;
	
	if (*((DWORD*)(pData + 0x28)) != 0xddc776f3)
	{
		DEBUGMSG("Wrong signature: #%08x\n", *((DWORD*)(pData + 0x28)));
		delete[] pData;
		return NULL;
	}

	if (! hmFLibHandle)
	{
		int iOldError = SetErrorMode(SEM_NOOPENFILEERRORBOX);
		
		hmFLibHandle = LoadLibrary("Riched20.dll");
		if ((int)hmFLibHandle < HINSTANCE_ERROR)
			hmFLibHandle = LoadLibrary("RICHED32.DLL");
			
		if ((int)hmFLibHandle < HINSTANCE_ERROR) 
			hmFLibHandle = NULL;
		SetErrorMode(iOldError);
	}

	iLastLoadTime = GetTickCount();

	GetClientRect(hwParentWin, &rRect);
	// Create window invisbile, only show when data fully loaded!
	hWnd = CreateWindow("RichEdit20A", "", WS_CHILD | ES_MULTILINE | ES_READONLY |
		                        WS_HSCROLL | WS_VSCROLL | ES_NOHIDESEL,
		rRect.left, rRect.top, rRect.right - rRect.left,
		rRect.bottom - rRect.top, hwParentWin, NULL, hInst, NULL);
	if (! hWnd)
		hWnd = CreateWindow("RichEdit", "", WS_CHILD | ES_MULTILINE | ES_READONLY |
		                        WS_HSCROLL | WS_VSCROLL | ES_NOHIDESEL,
		rRect.left, rRect.top, rRect.right - rRect.left,
		rRect.bottom - rRect.top, hwParentWin, NULL, hInst,NULL);
	if (hWnd)
	{
		SendMessage(hWnd, EM_SETMARGINS, EC_LEFTMARGIN, 8);
		SendMessage(hWnd, EM_SETEVENTMASK, 0, ENM_UPDATE); //ENM_SCROLL doesn't work for thumb movements!

		PostMessage(hwParentWin, WM_COMMAND, MAKELONG(lcp_ansi,itm_fontstyle), (LPARAM)hWnd);

		char* szRes = ConvertData(pData, iL);
		int curColor = DEFAULT - 1;
		if (szRes)
		{
			SendMessage(hWnd, EM_SETBKGNDCOLOR, (WPARAM)FALSE, (LPARAM)(COLORREF)bgCol);
			szRes = ConvertToRTF(szRes);
			BYTE* pSrc = (BYTE*)szRes;
			EDITSTREAM stream = {(DWORD)&pSrc, 0, putCallback};
			SendMessage(hWnd, EM_STREAMIN, (WPARAM)(UINT)SF_RTF, (LPARAM)(EDITSTREAM FAR *)&stream);
			delete[] szRes;
			SendMessage(hWnd, EM_SETSEL, (WPARAM)0, (LPARAM)0);
			PostMessage(hwParentWin, WM_COMMAND, MAKELONG(0, itm_percent), (LPARAM)hWnd);
			bSucceed = true;
		}
		delete[] pData;
		DEBUGMSG("Processing result: %i\n", bSucceed)
		if (! bSucceed)
		{
			DestroyWindow(hWnd);
			hWnd = NULL;
		}
	}
	if (hWnd)
		ShowWindow(hWnd, SW_SHOW);
	DEBUGMSG("Converted in %i msec\n\n", GetTickCount() - iLastLoadTime)
	iLastLoadTime = GetTickCount();
	return hWnd;
}


int __stdcall ListNotificationReceived(HWND hwListWin, int iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_COMMAND:
		if (HIWORD(wParam) == EN_UPDATE && abs(GetCurrentTime() - iLastLoadTime) > 1000)
		{
			int iFirstVisible = SendMessage(hwListWin, EM_GETFIRSTVISIBLELINE, 0, 0);
			int iLineCount = SendMessage(hwListWin, EM_GETLINECOUNT, 0, 0);
			if (iLineCount > 0)
			{
				int iPercent = MulDiv(iFirstVisible, 100, iLineCount);
				PostMessage(GetParent(hwListWin), WM_COMMAND, MAKELONG(iPercent, itm_percent), (LPARAM)hwListWin);
			}
			return 0;
		}
		break;
	case WM_NOTIFY:
		break;
	case WM_MEASUREITEM:
		break;
	case WM_DRAWITEM:
		break;
	}
	return 0;
}

int __stdcall ListSendCommand(HWND hwListWin, int iCommand,int iParameter)
{
	switch (iCommand)
	{
	case lc_copy:
		SendMessage(hwListWin, WM_COPY, 0, 0);
		return LISTPLUGIN_OK;
	case lc_newparams:
		return LISTPLUGIN_ERROR;
	case lc_selectall:
		SendMessage(hwListWin, EM_SETSEL, 0, -1);
		return LISTPLUGIN_OK;
	case lc_setpercent:
		int iFirstVisible = SendMessage(hwListWin, EM_GETFIRSTVISIBLELINE, 0, 0);
		int iLineCount = SendMessage(hwListWin, EM_GETLINECOUNT, 0, 0);
		if (iLineCount > 0)
		{
			int iPos = MulDiv(iParameter, iLineCount, 100);
			SendMessage(hwListWin, EM_LINESCROLL, 0, iPos - iFirstVisible);
			iFirstVisible = SendMessage(hwListWin, EM_GETFIRSTVISIBLELINE, 0, 0);
			// Place caret on first visible line!
			int iFirstChar = SendMessage(hwListWin, EM_LINEINDEX, iFirstVisible, 0);
			SendMessage(hwListWin, EM_SETSEL, iFirstChar, iFirstChar);
			iPos = MulDiv(iFirstVisible, 100, iLineCount);
			// Update percentage display
			PostMessage(GetParent(hwListWin), WM_COMMAND, MAKELONG(iPos, itm_percent), (LPARAM)hwListWin);
			return LISTPLUGIN_OK;
		}
		break;
	}
	return LISTPLUGIN_ERROR;
}

int _stdcall ListSearchText(HWND hwListWin, char* szSearchString, int iSearchParameter)
{
FINDTEXT ftFind;
int iStartPos = 0;
int iFlags = 0;

	if (iSearchParameter & lcs_findfirst)
	{
		//Find first: Start at top visible line
		iStartPos = SendMessage(hwListWin, EM_LINEINDEX, SendMessage(hwListWin, EM_GETFIRSTVISIBLELINE, 0, 0), 0);
		SendMessage(hwListWin, EM_SETSEL, iStartPos, iStartPos);
	}
	else
	{
		//Find next: Start at current selection+1
		SendMessage(hwListWin, EM_GETSEL, (WPARAM)&iStartPos, 0);
		iStartPos++;
	}

	ftFind.chrg.cpMin = iStartPos;
	ftFind.chrg.cpMax = SendMessage(hwListWin, WM_GETTEXTLENGTH, 0, 0);

	if (iSearchParameter & lcs_wholewords)
		iFlags |= FR_WHOLEWORD;
	if (iSearchParameter & lcs_matchcase)
		iFlags |= FR_MATCHCASE;
	if (!(iSearchParameter & lcs_backwards))
		iFlags |= FR_DOWN;
	ftFind.lpstrText = szSearchString;
	int iIndex = SendMessage(hwListWin, EM_FINDTEXT, iFlags, (LPARAM)&ftFind);
	if (iIndex != -1)
	{
	  int iIndexend = iIndex + strlen(szSearchString);
	  SendMessage(hwListWin, EM_SETSEL, iIndex, iIndexend);
	  int iLine = SendMessage(hwListWin, EM_LINEFROMCHAR, iIndex, 0) - 3;
	  if (iLine < 0) iLine = 0;
      iLine -= SendMessage(hwListWin, EM_GETFIRSTVISIBLELINE, 0, 0);
      SendMessage(hwListWin, EM_LINESCROLL, 0, iLine);
	  return LISTPLUGIN_OK;
	}
	else
		SendMessage(hwListWin, EM_SETSEL, -1, -1);  // Restart search at the beginning
	return LISTPLUGIN_ERROR;
}

void __stdcall ListCloseWindow(HWND hwListWin)
{
	DestroyWindow(hwListWin);
	return;
}

int __stdcall ListPrint(HWND hwListWin, char* szFileToPrint, char* szDefPrinter, int iPrintFlags, RECT* pMargins)
{
PRINTDLG pdPrintDlgRec;

	memset(&pdPrintDlgRec, 0, sizeof(PRINTDLG));
	pdPrintDlgRec.lStructSize = sizeof(PRINTDLG);

    pdPrintDlgRec.Flags		= PD_ALLPAGES | PD_USEDEVMODECOPIESANDCOLLATE | PD_RETURNDC;
	pdPrintDlgRec.nFromPage	= 0xFFFF; 
	pdPrintDlgRec.nToPage	= 0xFFFF; 
    pdPrintDlgRec.nMinPage	= 1;
    pdPrintDlgRec.nMaxPage	= 0xFFFF;
    pdPrintDlgRec.nCopies	= 1;
    pdPrintDlgRec.hwndOwner	= hwListWin;// MUST be Zero, otherwise crash!

	if (PrintDlg(&pdPrintDlgRec)) 
	{
		HDC hDC = pdPrintDlgRec.hDC;
		DOCINFO diDocInfo;
		POINT ptOffset, ptPhyssize, ptStart, ptAvail, ptPrintable;
		int iLogX, iLogY;
		RECT rRCsaved;

		// Warning: PD_ALLPAGES is zero!
		BOOL bPrintSel = pdPrintDlgRec.Flags & PD_SELECTION;
		BOOL bPrintPages = pdPrintDlgRec.Flags & PD_PAGENUMS;
		int iPageFrom = 1;
		int iPageTo = 0x7FFF;
		if (bPrintPages)
		{
			iPageFrom = pdPrintDlgRec.nFromPage;
			iPageTo = pdPrintDlgRec.nToPage;
			if (iPageTo <= 0) iPageTo = 0x7FFF;
		}


		memset(&diDocInfo, 0, sizeof(DOCINFO));
		diDocInfo.cbSize = sizeof(DOCINFO);
		diDocInfo.lpszDocName = szFileToPrint;
		if (StartDoc(hDC, &diDocInfo))
		{
			SetMapMode(hDC, MM_LOMETRIC);
			ptOffset.x = GetDeviceCaps(hDC, PHYSICALOFFSETX);
			ptOffset.y = GetDeviceCaps(hDC, PHYSICALOFFSETY);
			DPtoLP(hDC, &ptOffset, 1);
			ptPhyssize.x = GetDeviceCaps(hDC, PHYSICALWIDTH);
			ptPhyssize.y = GetDeviceCaps(hDC, PHYSICALHEIGHT);
			DPtoLP(hDC, &ptPhyssize, 1);

			ptStart.x = pMargins->left - ptOffset.x;
			ptStart.y = -pMargins->top - ptOffset.y;
			if (ptStart.x < 0) ptStart.x = 0;
			if (ptStart.y > 0) ptStart.y = 0;
			ptAvail.x = GetDeviceCaps(hDC, HORZRES);
			ptAvail.y = GetDeviceCaps(hDC,VERTRES);
			DPtoLP(hDC, &ptAvail, 1);

			ptPrintable.x = min(ptPhyssize.x - (pMargins->right + pMargins->left), ptAvail.x - ptStart.x);
			ptPrintable.y = max(ptPhyssize.y + (pMargins->top + pMargins->bottom), ptAvail.y - ptStart.y);
  			
			iLogX = GetDeviceCaps(hDC, LOGPIXELSX);
			iLogY = GetDeviceCaps(hDC, LOGPIXELSY);

			SendMessage(hwListWin, EM_FORMATRANGE, 0, 0);

			FORMATRANGE frRange;
			memset(&frRange, 0, sizeof(FORMATRANGE));
			frRange.hdc = hDC;
			frRange.hdcTarget = hDC;
			LPtoDP(hDC, &ptStart, 1);
			LPtoDP(hDC, &ptPrintable, 1);
			frRange.rc.left = ptStart.x * 1440 / iLogX;
			frRange.rc.top = ptStart.y * 1440 / iLogY;
			frRange.rc.right = (ptStart.x + ptPrintable.x) * 1440 / iLogX;
			frRange.rc.bottom = (ptStart.y + ptPrintable.y) * 1440 / iLogY;
			SetMapMode(hDC, MM_TEXT);

			BOOL bPrintAborted = false;
			frRange.rcPage = frRange.rc;
			rRCsaved = frRange.rc;
			int iCurrentPage = 1;
			int iLastChar = 0;
			int iLastChar2= 0;
			int iMaxLen = SendMessage(hwListWin, WM_GETTEXTLENGTH, 0, 0);
			frRange.chrg.cpMax = -1;
			if (bPrintPages)
			{
				do
				{
			        frRange.chrg.cpMin = iLastChar;
					if (iCurrentPage < iPageFrom)
						iLastChar = SendMessage(hwListWin, EM_FORMATRANGE, 0, (LPARAM)&frRange);
					else
						//waitform.ProgressLabel.Caption:=spage+inttostr(CurrentPage);
						//application.processmessages;
						iLastChar = SendMessage(hwListWin, EM_FORMATRANGE, 1, (LPARAM)&frRange);
					// Warning: At end of document, LastChar may be<MaxLen!!!
					if (iLastChar != -1 && iLastChar < iMaxLen)
					{
						frRange.rc = rRCsaved;                // Check whether another page comes
						frRange.rcPage = frRange.rc;
						frRange.chrg.cpMin = iLastChar;
						iLastChar2 = SendMessage(hwListWin, EM_FORMATRANGE, 0, (LPARAM)&frRange);
						if (iLastChar < iLastChar2 && iLastChar < iMaxLen && iLastChar != -1 &&
						  iCurrentPage >= iPageFrom && iCurrentPage < iPageTo) EndPage(hDC);
					}

					iCurrentPage++;
					frRange.rc = rRCsaved;
					frRange.rcPage = frRange.rc;
				}
				while (iLastChar < iMaxLen && iLastChar != -1 && iLastChar < iLastChar2 &&
					     (bPrintPages && iCurrentPage <= iPageTo) && !bPrintAborted);
			}
			else
			{
				if (bPrintSel)
				{
					SendMessage(hwListWin, EM_GETSEL, (WPARAM)&iLastChar, (LPARAM)&iMaxLen);
					frRange.chrg.cpMax = iMaxLen;
				}
				do
				{
					frRange.chrg.cpMin = iLastChar;
					//waitform.ProgressLabel.Caption:=spage+inttostr(CurrentPage);
					//waitform.ProgressLabel.update;
					//application.processmessages;
					iLastChar = SendMessage(hwListWin, EM_FORMATRANGE, 1, (LPARAM)&frRange);

					// Warning: At end of document, LastChar may be<MaxLen!!!
					if (iLastChar != -1 && iLastChar < iMaxLen)
					{
						frRange.rc = rRCsaved;                // Check whether another page comes
						frRange.rcPage = frRange.rc;
						frRange.chrg.cpMin = iLastChar;
						iLastChar2 = SendMessage(hwListWin, EM_FORMATRANGE, 0, (LPARAM)&frRange);
						if (iLastChar < iLastChar2 && iLastChar < iMaxLen && iLastChar != -1)
							EndPage(hDC);
					}
					iCurrentPage++;
					frRange.rc = rRCsaved;
					frRange.rcPage = frRange.rc;
				}
				while (iLastChar < iLastChar2 && iLastChar < iMaxLen && iLastChar != -1 && !bPrintAborted);
			}
			if (bPrintAborted)
				AbortDoc(hDC);
			else
				EndDoc(hDC);
		} //StartDoc
  
		SendMessage(hwListWin, EM_FORMATRANGE, 0, 0);
		DeleteDC(pdPrintDlgRec.hDC);
	}
	if (pdPrintDlgRec.hDevNames)
		GlobalFree(pdPrintDlgRec.hDevNames);
	return 0;
}

char* strlcpy(char* p, char* p2, int maxlen)
{
	if ((int)strlen(p2)>=maxlen)
	{
		strncpy(p,p2,maxlen);
		p[maxlen]=0;
	}
	else
		strcpy(p, p2);
	return p;
}

void __stdcall ListGetDetectString(char* szDetectString,int iMaxLen)
{
	strlcpy(szDetectString, parsefunction, iMaxLen);
}

void __stdcall ListSetDefaultParams(ListDefaultParamStruct* dps)
{
	
}
