// gfxview.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "listplug.h"
#include "view.h"
#include <stdio.h>
#include <stdlib.h>

#define parsefunction ""
//"SIZE=24576|SIZE=18432|SIZE=13824|SIZE=12288|SIZE=6912|SIZE=6144|SIZE=3072|SIZE=2048|SIZE=1536|SIZE=768|EXT=\"888\"|(EXT=\"plc\"|([0]=\"L\"&[1]=\"C\"&[2]=\"M\"&[3]=\"P\"&[4]=\"5\")|([0]=17&[1]=0&[3]=217))|(EXT=\"bit\"|([0]=\"B\"&[1]=\"I\"&[2]=\"T\")"
char inifilename[MAX_PATH] = "defaultinifile.ini";
const char inifile[] = "inX.cfg";
const char appname[] = "gfxview";

LRESULT CALLBACK WndProc(HWND hWin, UINT uiMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE hInst = 0;
HWND hWnd = NULL;
int iFit = 0;
int iFilter = 0;
int iScale = 100;
int iBright = 0;
DWORD dwBorder = 0;

DWORD dwCols[16] = {0x000000, 0x000080, 0x800000, 0x800080, 0x008000, 0x008080, 0x808000, 0x808080,
					0x000000, 0x0000ff, 0xff0000, 0xff00ff, 0x00ff00, 0x00ffff, 0xffff00, 0xffffff};
DWORD defPal[16] = {0x000000, 0x800000, 0x000080, 0x800080, 0x008000, 0x808000, 0x008080, 0x808080,
					0x000000, 0xff0000, 0x0000ff, 0xff00ff, 0x00ff00, 0xffff00, 0x00ffff, 0xffffff};

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
LPTSTR pCmd;
char szTmp[256];
DWORD tmp;
int i;

    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			hInst=(HINSTANCE)hModule;
			pCmd = GetCommandLine();
			strcpy(inifilename, pCmd + (*pCmd == '\"'));
			pCmd = strrchr(inifilename, '\\') + 1;
			strcpy(pCmd, inifile);
			// loading settings
			iScale = GetPrivateProfileInt(appname, "scale", 200, inifilename);
			if (! iScale) iFit = 1, iScale = 200;
			if (iScale > 1000) iScale = 1000;
			if (iScale < 0) iScale = 0;
			iFilter = GetPrivateProfileInt(appname, "filter", 0, inifilename);
			tmp = GetPrivateProfileInt(appname, "border", 0, inifilename);
			dwBorder = ((tmp & 0xff0000) >> 16) + (tmp & 0xff00) + ((tmp & 0xff) << 16);
			iBright = GetPrivateProfileInt(appname, "bright", 0, inifilename);
			if (iBright) iBright = 8;
			GetPrivateProfileString(appname, "palette", NULL, szTmp, 255, inifilename);
			pCmd = szTmp;
			while (*pCmd)
			{
				if (*pCmd == ' ')
				{
					*pCmd = 0;
					break;
				}
				pCmd++;
			}
			if (*szTmp)
			{
				char szNm[8];
				for (i = 0; i < 16; i++)
				{
					sprintf(szNm, "%i", i);
					tmp = GetPrivateProfileInt(szTmp, szNm, defPal[i], inifilename);
					tmp = ((tmp & 0xff0000) >> 16) + (tmp & 0xff00) + ((tmp & 0xff) << 16);
					dwCols[i] = tmp;
				}
			}
			break;
		case DLL_PROCESS_DETACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
    }
    return TRUE;
}


HWND __stdcall ListLoad(HWND hwParentWin, char* szFileToLoad, int iShowFlags)
{
HDC hParDC = NULL;
RECT rRect;
DWORD dwW2 = 0;
BYTE* pData = NULL;
char* szStr = NULL;


	szStr = strrchr(szFileToLoad, '\\');
	if (! szStr) return NULL;
	szStr = strrchr(szStr, '.');
	if (!szStr) return NULL;

	HANDLE hFile = CreateFile(szFileToLoad, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
							FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return NULL;

	int iL = GetFileSize(hFile, NULL);
	if (iL >= 49152) 
	{
		CloseHandle(hFile);
		return NULL;
	}

	pData = new BYTE[49152];	//256 cols for 256x192
	DWORD x = 0;
	CView* pView = NULL;
	if (pData)
	{
		ReadFile(hFile, pData, iL, &dwW2, NULL);
			
		if (szStr[1] == '$')	//hobeta
		{
			memcpy(szStr + 1, pData + 8, 3);
			iL = *((WORD*)(pData + 11));
			memcpy(pData, pData + 17, iL);
		}

		if (! stricmp(szStr, ".888"))
		{
			pView = new C8colView(pData);
			iL = 0;
		}
			
		if ((*((DWORD*)pData) == 0x504d434c) || (*((DWORD*)(pData + 3)) == 0x8e11d9))
		{
			pView = new CLCView(pData);
			iL = 0;
		}
			
		if ((*pData == 'B' && pData[1] == 'I' && pData[2] == 'T'))
		{
			pView = new CBitView(pData);
			iL = 0;
		}
			
		if ((iL == 1536) || (iL == 3072))
		{
			if (iL == 1536) 
				pView = new CChunkView(pData);
			else
				pView = new CChunkUnpView(pData);
			iL = 0;
		}

		if (iL == 12288)
		{
			pView = new CMCView(pData);
			iL = 0;
		}

		if (iL == 24576)
		{
			pView = new CMCXView(pData);
			iL = 0;
		}

		if (*pData)
		{
			int flg = 0;
			int iDat = 5 + 3 * *pData;
			for (int i = 0; i < *pData; i++)
			{
				if (flg = (i * 3 + 3 >= iL)) break;
				BYTE w = pData[i * 3 + 1];
				BYTE h = pData[i * 3 + 2];
				BYTE l = pData[i * 3 + 3];
				if (flg = (w > 32 || h > 24 || !(l == 8 || l == 9 || l == 16 || l == 17))) break;
				iDat += w * h * l;
			}
			flg |= (iDat != iL);
			if (! flg)
			{
				pView = new CSpriteView(pData);
				iL = 0;
			}
		}

		switch (iL)
		{
		case 0:
			break;

		case 768:
			memcpy(pData + 256, pData, 768);
			memset(pData, 0, 256);
			memset(pData + 1024, 0, 1024);
		case 2048:
			pView = new CFontView(pData);
			break;

		case 6144:
			{
			for (x = 6144; x < 6912; x++)
					pData[x] = 7;	// reset attrs
			}
		case 6912:
			pView = new CScrView(pData);
			break;

		case 13824:
			pView = new CDblView(pData);
			break;

		case 18432:
			pView = new CTriView(pData);
			break;
		}

		delete[] pData;
	}
	CloseHandle(hFile);

	if (! pView) return NULL;

	GetClientRect(hwParentWin, &rRect);

WNDCLASS wcl;

	if (! GetClassInfo(hInst, "GFXCLASS", &wcl))
	{
		wcl.cbClsExtra = 0;
		wcl.cbWndExtra = 0;
		wcl.hbrBackground = NULL;//CreateSolidBrush(dwCols[iBorder]);
		wcl.hCursor = LoadCursor(hInst, IDC_ARROW);
		wcl.hIcon = NULL;
		wcl.hInstance = hInst;
		wcl.lpfnWndProc = WndProc;
		wcl.lpszClassName = "GFXCLASS";
		wcl.lpszMenuName = NULL;
		wcl.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

		RegisterClass(&wcl);
	}

	// Create window invisbile, only show when data fully loaded!
	hWnd = CreateWindow("GFXCLASS", "", WS_CHILD,
						rRect.left, rRect.top, rRect.right - rRect.left,
						rRect.bottom - rRect.top, hwParentWin, NULL, hInst, NULL);
	
	if (hWnd)
	{
		SetWindowLong(hWnd, GWL_USERDATA, (LONG)pView);
		SetTimer(hWnd, 1, 500, NULL);
		ShowWindow(hWnd, SW_SHOW);
	}
	else
		delete pView;
	
	return hWnd;
}

LRESULT CALLBACK WndProc(HWND hWin, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
CView* pView = (CView*)GetWindowLong(hWin, GWL_USERDATA);
static HBRUSH hBr = CreateSolidBrush(dwBorder);

	switch (uiMsg)
	{
	case WM_ERASEBKGND:
		return 1;
	case WM_PAINT:
		{
			if (pView)
			{
				RECT hRect;
				PAINTSTRUCT psStruct;
				HDC hWDC = BeginPaint(hWin, &psStruct);
				GetClientRect(hWin, &hRect);
//				if (psStruct.fErase)
					FillRect(hWDC, &hRect, hBr);
				
				int iWid = hRect.right - hRect.left;
				int iHei = hRect.bottom - hRect.top;
				pView->Draw(hWDC, iWid, iHei);

				EndPaint(hWin, &psStruct);
			}
			return 0;
		}
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_ADD:
				if (iScale < 1000) iScale += 100;
				break;
			case VK_SUBTRACT:
				if (iScale > 100) iScale -= 100;
				break;
			case VK_PRIOR:
				pView->PrewMode();
				break;
			case VK_NEXT:
				pView->NextMode();
				break;
			case VK_RETURN:
				iFilter = !iFilter;
				break;
			case 'B':
				iBright ^= 8;
				pView->Render();
				break;
			case 'I':
				pView->Invert();
				pView->Render();
				break;
			case 'S':
				{
				OPENFILENAME opstruct;
				char szTmp[256];

				*szTmp = 0;
				opstruct.lStructSize = sizeof(opstruct);
				opstruct.hwndOwner = hWin;
				opstruct.hInstance = hInst;
				opstruct.lpstrFilter = "*.bmp";
				opstruct.lpstrCustomFilter = NULL;
				opstruct.nFilterIndex = 0;
				opstruct.lpstrFile = szTmp;
				opstruct.nMaxFile = 256;
				opstruct.lpstrFileTitle = NULL;
				opstruct.lpstrInitialDir = szTmp;
				opstruct.lpstrTitle = "Save image as:";
				opstruct.Flags = OFN_OVERWRITEPROMPT;
				opstruct.lpfnHook = NULL;
				opstruct.lCustData = 0;
				opstruct.lpstrDefExt = "bmp";
				opstruct.lpTemplateName = NULL;

				GetSaveFileName(&opstruct);
				pView->Save(szTmp);
				}
			default:
				return 0;
			}
			
			pView->Invalidate();
			InvalidateRect(hWin, NULL, FALSE);
		}
		break;
	case WM_TIMER:
		{
			if (pView->Animate())
			{
				pView->Invalidate();
				InvalidateRect(hWin, NULL, 0);
			}
		}
		break;
	case WM_CLOSE:
		delete pView;
	default:
		return DefWindowProc(hWin, uiMsg, wParam, lParam);
	}
	return 0;
}

int __stdcall ListNotificationReceived(HWND hwListWin, int iMessage, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

int __stdcall ListSendCommand(HWND hwListWin, int iCommand,int iParameter)
{
	if (iCommand == lc_newparams)
	{
		iFit = iParameter & lcp_fittowindow;
		InvalidateRect(hwListWin, NULL, 1);
		return LISTPLUGIN_OK;
	}
	return LISTPLUGIN_ERROR;
}

int _stdcall ListSearchText(HWND hwListWin, char* szSearchString, int iSearchParameter)
{
	return LISTPLUGIN_ERROR;
}

void __stdcall ListCloseWindow(HWND hwListWin)
{
	delete (CView*)GetWindowLong(hwListWin, GWL_USERDATA);
	DestroyWindow(hwListWin);
	return;
}

int __stdcall ListPrint(HWND hwListWin, char* szFileToPrint, char* szDefPrinter, int iPrintFlags, RECT* pMargins)
{
	return LISTPLUGIN_ERROR;
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
//	strlcpy(inifilename, dps->DefaultIniName, MAX_PATH - 1);
}

 //  winspool.lib comdlg32.lib  shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib