// VSPPlay.h: interface for the CVSPPlay class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VSPPLAY_H__C354C317_E5B3_476E_BB1D_A22D78137A6C__INCLUDED_)
#define AFX_VSPPLAY_H__C354C317_E5B3_476E_BB1D_A22D78137A6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ScaleFilter.h"

#pragma pack(1)

class CVSPPlayerDlg;

class CVSPPlay  
{

struct SVSPFileHeader
{
	char m_cSignature[2];
	BYTE m_bVersion;
	char m_cFileName[8];
	WORD m_wFrames;
	BYTE m_bDelay;
	BYTE m_bPacked;
	BYTE m_bColor;
	BYTE m_dwReserved;
	BYTE m_cClipName[32];
	BYTE m_cClipAuthor[32];
	BYTE m_bBlockSize[175];
};

public:
	CVSPPlay();
	virtual ~CVSPPlay();

	int OpenFile(const char* szFileName);

	int OpenStream(void* pStream);
	int RenderFrame(int iShow = 1);
	int GetFrame();
	int GetFrames();
	void Delay();

	void Rewind();
	void GotoFrame(int iFrame);

	void DrawFrame(CDC* pDC);
	void UpdateSize(int iXSize, int iYSize);

	void SetFilter(int iFilter);
	int GetFilter() {return m_iFilter;}

	friend CVSPPlayerDlg;
private:
	enum EModes
	{
		EBitpack = 1,
		EDeltapack = 2,
		EExtpack = 4,
		EExtcol = 8
	};

	void _Render();
	void _depack(DWORD& dwScr, BYTE*& pStr, int iBitpack);
	void _depcol(BYTE*& pAtr, BYTE*& pStr);
	void _skip(DWORD& dwScr, int iSkip);

	BYTE* m_pFilebuf;

	BYTE* m_pScreen;
	BYTE* m_pAttr;
	BYTE* m_pSprite;
	BITMAPINFO m_biBitmap;
	RGBQUAD m_rgbqQuad[7];

	CScaleFilter* m_pFilter;
	int m_iFrameX;
	int m_iFrameY;
	int m_iXPos;
	int m_iYPos;
	BYTE* m_pStream;
	DWORD m_dwOffset;

	WORD m_wFrame;

	SVSPFileHeader m_svspfhHeader;

	int m_iFilter;

};

#endif // !defined(AFX_VSPPLAY_H__C354C317_E5B3_476E_BB1D_A22D78137A6C__INCLUDED_)
