// VSPPlay.cpp: implementation of the CVSPPlay class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VSPPlayer.h"
#include "VSPPlay.h"

#include "FileDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MAX_VERSION 8

#define CONT 254
#define COMMAND 255

#define NEWKADR 1
#define V_END   2
#define CH_SPD  3
#define SCREEN  4
#define GROUP   5
#define LGROUP  6
#define LSCREEN 7
#define BPMODE  8
#define DPMODE  9

//DPMODE +1 byte

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVSPPlay::CVSPPlay()
{
	m_pScreen = new BYTE[6912];
	m_pSprite = new BYTE[6144 * 8 + 260];
	m_pAttr = m_pScreen + 6144;

	m_biBitmap.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_biBitmap.bmiHeader.biWidth = 256;
	m_biBitmap.bmiHeader.biHeight = 192;
	m_biBitmap.bmiHeader.biPlanes = 1;
	m_biBitmap.bmiHeader.biBitCount = 8;
	m_biBitmap.bmiHeader.biCompression = BI_RGB;
	m_biBitmap.bmiHeader.biSizeImage = 6144 * 8;
	m_biBitmap.bmiHeader.biXPelsPerMeter = 10000;
	m_biBitmap.bmiHeader.biYPelsPerMeter = 10000;
	m_biBitmap.bmiHeader.biClrUsed = 0;
	m_biBitmap.bmiHeader.biClrImportant = 0;

	m_pStream = m_pFilebuf = NULL;
	m_dwOffset = 0;

	m_wFrame = 0xffff;

	memset(&m_svspfhHeader, 0, sizeof(m_svspfhHeader));
	m_svspfhHeader.m_bDelay = 1;

	memset(m_pScreen, 0, 6144);
	memset(m_pAttr, 7, 768);
	memset(m_pSprite, 0, 49152 + 260);
	memset(m_biBitmap.bmiColors, 0, 4);

	m_pFilter = NULL;
	m_iFrameX = 256;
	m_iFrameY = 192;

	SetFilter(0);
}

CVSPPlay::~CVSPPlay()
{
	delete[] m_pScreen;
	delete[] m_pSprite;
	delete[] m_pFilebuf;
	delete m_pFilter;
}

int CVSPPlay::OpenFile(const char* szFileName)
{
HANDLE hFile = CreateFile(szFileName,
						  GENERIC_READ,
						  FILE_SHARE_READ,
						  NULL,
						  OPEN_EXISTING,
						  FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS,
						  NULL);

	if (! hFile) return 0;

DWORD dwSize = GetFileSize(hFile, NULL);
DWORD dwTmp;

	if (! (dwSize + 1)) return 0;	

	delete[] m_pFilebuf;
	
	m_pFilebuf = new BYTE[dwSize];

	ReadFile(hFile, m_pFilebuf, dwSize, &dwTmp, NULL);

	CloseHandle(hFile);

	int iC = strlen(szFileName) - 1;
	while (szFileName[iC] != '.') iC--;

	iC++;

CString csTmp(szFileName);

	csTmp.MakeUpper();

	if (!strcmp((LPCTSTR)csTmp + iC, "VSP")) return OpenStream(m_pFilebuf);

	if (!strcmp((LPCTSTR)csTmp + iC, "TRD"))
	{
		CFileDlg cfdFiles;
		int iFil = 0;
		CString csNames[16];
		int iOffsets[16];
		char szTmp[9];

		int iFile = 0;
		iC = 8;
		do
		{
		if (*((DWORD*)(m_pFilebuf + iC)) == 0x505356)
		{
			iOffsets[iFile] = 4096 * m_pFilebuf[iC + 7] + 256 * m_pFilebuf[iC + 6];
			memcpy(szTmp, m_pFilebuf + iC - 8, 8);
			szTmp[8] = 0;
			csNames[iFile] = CString(szTmp);
			iFile++;
		}
		iC += 16;
		}
		while (m_pFilebuf[iC - 8]);

		if (iFile)
		{
			if (iFile == 1)
				return OpenStream(m_pFilebuf + iOffsets[0]);
			cfdFiles.Create(IDD_FILEDIALOG);
			for (iC = 0; iC < iFile; iC++)
				cfdFiles.m_clbFiles.AddString(csNames[iC]);
			
			cfdFiles.ShowWindow(SW_SHOW);
			if (cfdFiles.RunModalLoop() == IDOK)
				return OpenStream(m_pFilebuf + iOffsets[cfdFiles.m_clbFiles.GetCurSel()]);
		}
		
		AfxMessageBox("No videofiles found!", MB_OK);
		m_wFrame = 0xffff;
		delete[] m_pFilebuf;
		m_pFilebuf = m_pStream = NULL;
		return 0;
	}

	if (!strcmp((LPCTSTR)csTmp + iC, "SCL"))
	{
		CFileDlg cfdFiles;
		int iFil = 0;
		CString csNames[16];
		int iOffsets[16];
		char szTmp[9];
		int iFile = 0;

		int iFilez = 0;
		int iSize = 0;

		iC = 17;
		do
		{
		if (*((DWORD*)(m_pFilebuf + iC)) == 0x505356)
		{
			iOffsets[iFile] =  + 256 * iSize + 9 + 14 * m_pFilebuf[8];
			memcpy(szTmp, m_pFilebuf + iC - 8, 8);
			szTmp[8] = 0;
			csNames[iFile] = CString(szTmp);
			iFile++;
		}
		iSize += m_pFilebuf[iC + 5];
		iFilez++;
		iC += 14;
		}
		while (iFilez < m_pFilebuf[8]);

		if (iFile)
		{
			if (iFile == 1)
				return OpenStream(m_pFilebuf + iOffsets[0]);
			cfdFiles.Create(IDD_FILEDIALOG);
			for (iC = 0; iC < iFile; iC++)
				cfdFiles.m_clbFiles.AddString(csNames[iC]);
			
			cfdFiles.ShowWindow(SW_SHOW);
			if (cfdFiles.RunModalLoop() == IDOK)
				return OpenStream(m_pFilebuf + iOffsets[cfdFiles.m_clbFiles.GetCurSel()]);
		}

		AfxMessageBox("No videofiles found!", MB_OK);
		m_wFrame = 0xffff;
		delete[] m_pFilebuf;
		m_pFilebuf = m_pStream = NULL;
	}
	return 0;
}


int CVSPPlay::OpenStream(void* pStream)
{
	if (!pStream) return 0;

	m_pStream = (BYTE*)pStream;
	m_dwOffset = 0;

	memcpy(&m_svspfhHeader, pStream, 256);

	if (*((WORD*)m_svspfhHeader.m_cSignature) != 0x5356) 
	{
		AfxMessageBox("Invalid stream!", MB_OK);
		m_wFrame = 0xffff;
		return 0;
	}
	if (m_svspfhHeader.m_bVersion >= MAX_VERSION)
	{
		AfxMessageBox("Unsupported version!", MB_OK);
		m_wFrame = 0xffff;
		return 0;
	}

	m_dwOffset = 256;
	m_wFrame = 0;
	memset(m_pScreen, 0, 6144);

	if (m_svspfhHeader.m_bVersion < 2) m_dwOffset += 2048;

	if (! m_svspfhHeader.m_bColor) m_svspfhHeader.m_bColor = 7;
	m_svspfhHeader.m_bColor &= 63;

	memset(m_pAttr, m_svspfhHeader.m_bColor, 768);
	for (int i = 0; i < 8; i++)
	{
		m_biBitmap.bmiColors[i].rgbBlue = (i & 1) ? 255 : 0;
		m_biBitmap.bmiColors[i].rgbRed = (i & 2) ? 255 : 0;;
		m_biBitmap.bmiColors[i].rgbGreen = (i & 4) ? 255 : 0;;
	}

	return RenderFrame();
}

int CVSPPlay::RenderFrame(int iShow)
{
BYTE* pStream = m_pStream + m_dwOffset;
DWORD dwScreen = 0;
BYTE* pAttr = m_pAttr;

#define EX_V_END 255
#define EX_NEWFRM 31
#define EX_KEYFRM 63

static int mode = 0;
int count = 0;
DWORD off = 0;
BYTE tmp = 0, tmp1 = 0;
BYTE* pStr = NULL;

	if (! m_wFrame)
		mode = 0;

int isColor = mode & EExtcol;

	while (1)
	{
		tmp = *pStream;
		tmp1 = pStream[1];
		if (mode & EExtpack)
		{
			pStream--;
			if (tmp == EX_V_END)
			{
				tmp = COMMAND;
				tmp1 = V_END;
			}
			else
				if (tmp == EX_NEWFRM)
				{
					tmp = COMMAND;
					tmp1 = NEWKADR;
				}
				else
					if (tmp == EX_KEYFRM)
					{
						tmp = COMMAND;
						tmp1 = LSCREEN;
					}
					else
					{
						pStream += 2;
						for (int i = 0; i < 8; i++, tmp >>= 1)
							if (tmp & 1)
							{
								tmp1 = *pStream++;

								if (! tmp1)
								{
									while (isColor)
									{
										tmp = *pStream++;
										for (i = 0; i < 8; i++, tmp >>= 1)
											if (tmp & 1)
												pAttr += *pStream++;
											else
											{
												tmp1 = *pStream++;
												*pAttr++ = tmp1 & 0x3f;
												if (tmp1 & 128)
												{
													isColor = 0;
													break;
												}
											}
									}
									break;
								}

								_skip(dwScreen, tmp1);
							}
							else
								_depack(dwScreen, pStream, EBitpack);

						if (isColor)
						{
							tmp = *pStream++;
							for (i = 0; i < 8; i++, tmp >>= 1)
								if (tmp & 1)
									pAttr += *pStream++;
								else
								{
									tmp1 = *pStream++;
									*pAttr++ = tmp1 & 0x3f;
									if (tmp1 & 128)
									{
										isColor = 0;
										break;
									}
								}
						}
						continue;
					}
			}

		if (tmp == COMMAND)
		{
			pStream++;
			if (tmp1 == NEWKADR)
			{
				pStream++;
				break;
			}
			if (tmp1 == V_END)
			{
				m_wFrame = 0xffff;
				return 0;
			}

			if (tmp1 == CH_SPD)
			{
				pStream++;
				continue;
			}

			if (tmp1 == SCREEN)
			{
				dwScreen = 0;
				tmp = *++pStream;
				pStream++;
				while (dwScreen < 6144)
				{
					count = 1;
					if (tmp == *pStream)
					{
						count = *++pStream;
						pStream++;
						if (! count) count = 256;
					}
							
					while (count--)
					{
						_depack(dwScreen, pStream, 0);
						if (count) pStream -= 8;
					}
				}
				break;
			}

			if (tmp1 == GROUP)
			{
				count = *++pStream;
				pStream++;
				while (count--)
				{
					_depack(dwScreen, pStream, 0);
				}
				continue;
			}

			if (tmp1 == LGROUP)
			{
				count = *++pStream;
				pStream++;
				while (count--)
				{
					_depack(dwScreen, pStream, mode | EBitpack);
				}
				continue;
			}

			if (tmp1 == LSCREEN)
			{
				dwScreen = 0;
				pStream++;
				while (*pStream != 0xff)
					switch (*pStream++)
					{
						case 0:
							count = *pStream++;
							if (! count) count = 256;
							while (count--)
							{
								_depack(dwScreen, pStream, EBitpack);
								if (!(dwScreen & 31) && (mode & EExtcol)) _depcol(pAttr, pStream);
							}
							break;

						case 1:
							count = *pStream++;
							if (! count) count = 256;
							pStr = pStream;
							while (count--)
							{
								BYTE* oldstr = pStr;
								_depack(dwScreen, (pStr == pStream) ? pStream : pStr, EBitpack);
								if (!(dwScreen & 31) && (mode & EExtcol)) _depcol(pAttr, pStream);
								pStr = oldstr;
							}
							break;

						default:
							AfxMessageBox("Wrong LSCREEN marker!");
							break;
					}
				pStream++;
				break;
			}

			if (tmp1 == BPMODE)
			{
				mode |= EBitpack;
				pStream++;
				continue;
			}

			if (tmp1 == DPMODE)
			{
				pStream++;
				mode |= (*pStream++ & 7) << 1;
				continue;
			}

			AfxMessageBox("Wrong command!");
		}	// command

		if (tmp == CONT)
		{
			_skip(dwScreen, 0xfe);
			pStream++;
			continue;
		}

		_skip(dwScreen, *pStream++);
		_depack(dwScreen, pStream, mode);
	}


	if (dwScreen < 6145)
	{
		m_dwOffset = pStream - m_pStream;
		m_wFrame++;
		if (iShow)
		{
			_Render();
			if ((m_iFrameX != 256) || (m_iFrameY != 192))
				m_pFilter->DoFilter(m_pSprite, m_iFrameX, m_iFrameY, m_iXPos, m_iYPos);
		}
		return 1;
	}
	m_wFrame = 0xffff;
	return 0;
}

void CVSPPlay::_depack(DWORD& dwScr, BYTE*& pStr, int iMode)
{
int i = 0;
BYTE* pScr = m_pScreen + dwScr;
	if (iMode & EBitpack)
	{
		BYTE mask = *pStr++;
		BYTE data = 0;
		BYTE delta = 0;
		for (i = 0; i < 8; i++)
		{
			if (mask & 1) delta = *pStr++;
			mask >>= 1;
			data ^= delta;
			if (iMode & EDeltapack)
				pScr[i << 8] ^= data;
			else
				pScr[i << 8] = data;
		}
	}
	else
		for (i = 0; i < 8; i++)
			pScr[i << 8] = *pStr++;
	dwScr++;
	if (dwScr & 0x700) dwScr += 0x700;
}

void CVSPPlay::_depcol(BYTE*& pAtr, BYTE*& pStr)
{
	BYTE oldcol = 0;
	if (pAtr > m_pAttr) oldcol = pAtr[-1];
	for (int j = 0; j < 4; j++)
	{
		BYTE mask = *pStr++;
		for (int i = 0; i < 8; i++, mask >>= 1)
		{
			if (mask & 1) oldcol = *pStr++;
			*pAtr++ = oldcol;
		}
	}
}


inline void CVSPPlay::_skip(DWORD& dwScr, int iSkip)
{
	dwScr += iSkip;
	if (dwScr & 0x700) dwScr += 0x700;
}

int CVSPPlay::GetFrame()
{
	return m_wFrame;
}

int CVSPPlay::GetFrames()
{
	return m_svspfhHeader.m_wFrames;
}

void CVSPPlay::Delay()
{
	Sleep(20 * m_svspfhHeader.m_bDelay);
}


void CVSPPlay::Rewind()
{
	OpenStream(m_pStream);
}

void CVSPPlay::GotoFrame(int iFrame)
{
	if (!m_svspfhHeader.m_wFrames) return;
	if (iFrame >= m_svspfhHeader.m_wFrames)
		iFrame = m_svspfhHeader.m_wFrames - 1;

	Rewind();
	while (iFrame--) RenderFrame(0);

	RenderFrame();
}

void CVSPPlay::DrawFrame(CDC* pDC)
{
	if ((m_iFrameX == 256) && (m_iFrameY == 192))
	::SetDIBitsToDevice(pDC->m_hDC, m_iXPos, m_iYPos, 256, 192, 0, 0, 0, 192, m_pSprite,
			&m_biBitmap, DIB_RGB_COLORS);
	else
		m_pFilter->Show(pDC);
}

void CVSPPlay::UpdateSize(int iXSize, int iYSize)
{
	if (3 * iXSize >= 4 * iYSize)	//width bigger than height
	{
		m_iFrameY = iYSize;
		m_iFrameX = 4 * m_iFrameY / 3;
		m_iYPos = 18;
		m_iXPos = (iXSize - m_iFrameX) / 2 + 3;
	}
	else
	{
		m_iFrameX = iXSize;
		m_iFrameY = 3 * m_iFrameX / 4;
		m_iXPos = 3;
		m_iYPos = (iYSize - m_iFrameY) / 2 + 18;
	}

	m_pFilter->DoFilter(m_pSprite, m_iFrameX, m_iFrameY, m_iXPos, m_iYPos);
}

void CVSPPlay::SetFilter(int iFilter)
{
	delete m_pFilter;

//	AfxMessageBox("filter");

	switch (iFilter)
	{
	case 1:
		m_pFilter = new CLinearScale; break;
	case 2:
		m_pFilter = new CBiquadraticScale; break;
	case 3:
		m_pFilter = new CBicubicScale; break;
	default:
		m_pFilter = new CNearestScale; break;
	}
	m_iFilter = iFilter;
	m_pFilter->DoFilter(m_pSprite, m_iFrameX, m_iFrameY, m_iXPos, m_iYPos);
}

void CVSPPlay::_Render()
{
BYTE* pSrc = m_pScreen;
BYTE* pDst = m_pSprite;
	_asm
	{
		mov esi, pSrc
		mov edi, pDst
		add edi, 49152 - 256
		xor ebx, ebx
		mov ecx, 6144
		mov ah, 0x80	//mask
		cld
line:
		push ebx
		push ecx
nexby:	
		test [esi + ebx], ah
		mov al, [esi + ecx]
		jz paper
		and al, 7
		jnc geco
paper:
		and al, 56
		ror al, 3
geco:	stosb
//		mov [edi], al
//		inc edi
		ror ah, 1
		jnc nexby
		inc ecx
		inc ebx
		test bl, 31
		jnz nexby
		pop ecx
		pop ebx
		sub edi, 512
		inc bh
		test bh, 7
		jnz line
		add ecx, 32
		add bl, 32
		jc addok
		sub bh, 8
addok:	cmp bh, 0x18
		jc line
	}
}
