// ScaleFilter.cpp: implementation of the CScaleFilter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VSPPlayer.h"
#include "ScaleFilter.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScaleFilter::CScaleFilter()
{
	m_iXMax = GetSystemMetrics(SM_CXSCREEN);
	m_iYMax = GetSystemMetrics(SM_CYSCREEN);

	m_pImg = new DWORD[m_iXMax * m_iYMax];
	memset(m_pImg, 0, m_iXMax * m_iYMax);

	m_biBitmap.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_biBitmap.bmiHeader.biWidth = m_iXMax;
	m_biBitmap.bmiHeader.biHeight = m_iYMax;
	m_biBitmap.bmiHeader.biPlanes = 1;
	m_biBitmap.bmiHeader.biBitCount = 32;
	m_biBitmap.bmiHeader.biCompression = BI_RGB;
	m_biBitmap.bmiHeader.biSizeImage = m_iXMax * m_iYMax;
	m_biBitmap.bmiHeader.biXPelsPerMeter = 10000;
	m_biBitmap.bmiHeader.biYPelsPerMeter = 10000;
	m_biBitmap.bmiHeader.biClrUsed = 0;
	m_biBitmap.bmiHeader.biClrImportant = 0;

	RGBQUAD* pPal = m_rgbqPalette;
	for (int iCol = 0; iCol < 8; iCol++)
	{
		pPal->rgbBlue = iCol & 1 ? 0xff : 0;
		pPal->rgbRed = iCol & 2 ? 0xff : 0;
		pPal->rgbGreen = iCol & 4 ? 0xff : 0;
		pPal++;
	}

	m_iXImg = m_iYImg = 0;
}

CScaleFilter::~CScaleFilter()
{
	delete[] m_pImg;
}

void CScaleFilter::DoFilter(BYTE* pSrc, int iXImg, int iYImg, int iXPos, int iYPos)
{
	m_iXImg = iXImg;
	m_iYImg = iYImg;
	m_iXPos = iXPos;
	m_iYPos = iYPos;
	m_biBitmap.bmiHeader.biWidth = m_iXImg;
	m_biBitmap.bmiHeader.biHeight = m_iYImg;
	m_biBitmap.bmiHeader.biSizeImage = m_iXImg * m_iYImg;
}

void CScaleFilter::Show(CDC* pDC)
{
	::SetDIBitsToDevice(pDC->m_hDC, m_iXPos, m_iYPos, m_iXImg, m_iYImg, 0, 0, 0, m_iYImg, m_pImg,
			&m_biBitmap, DIB_RGB_COLORS);
}

//---------------------------------------------------------------------

void CNearestScale::DoFilter(BYTE* pSrc, int iXImg, int iYImg, int iXPos, int iYPos)
{
	CScaleFilter::DoFilter(pSrc, iXImg, iYImg, iXPos, iYPos);

	int iXStep = 0x10000 / iXImg;
	int iYStep = 0xc000 / iYImg;
	int xd = 0, yd = 0;
	for (int y = 0; y < iYImg; y++, yd += iYStep)
	{
		xd = 0;
		DWORD* pTo = m_pImg + y * iXImg;
		BYTE* pFrom = pSrc + (yd & 0xff00);
		for (int x = 0; x < iXImg; x++, xd += iXStep)
			*pTo++ = ((DWORD*)m_rgbqPalette)[pFrom[xd >> 8]];
	}
}


//-------------------------------

CLinearScale::CLinearScale() : CScaleFilter()
{
	m_pTable = NULL;
	m_pScaleTab = NULL;
}

CLinearScale::~CLinearScale()
{
	delete[] m_pScaleTab;
	delete[] m_pTable;
}

void CLinearScale::Init()
{
	m_pTable = new BYTE[8];
	_Calculate();
	RGBQUAD m_pLookup[16][64];

	for (int i = 0; i < 16; i++)
		for (int c = 0; c < 64; c++)
		{
			int j = c & (c >> 3);
			int k = c | (c >> 3);
			RGBQUAD tmp;
			int l = m_pTable[i];
			tmp.rgbBlue = j & 1 ? 255 : (k & 1 ? (c & 1 ? l : ~l) : 0);
			tmp.rgbRed = j & 2 ? 255 : (k & 2 ? (c & 2 ? l : ~l) : 0);
			tmp.rgbGreen = j & 4 ? 255 : (k & 4 ? (c & 4 ? l : ~l) : 0);
			m_pLookup[i][c] = tmp;
		}

	m_pScaleTab = new RGBQUAD[0x40000];
	for (i = 0; i < 0x40000; i++)
	{
		int c1 = i >> 12;
		int c2 = (i & 0xfc0) >> 6;
		int y = (i & 56) >> 3;
		int x = i & 7;
		RGBQUAD left = m_pLookup[y][c1];
		RGBQUAD right = m_pLookup[y][c2];
		RGBQUAD val;
		val.rgbBlue = left.rgbBlue + (right.rgbBlue - left.rgbBlue) * m_pTable[x] / 256;
		val.rgbRed = left.rgbRed + (right.rgbRed - left.rgbRed) * m_pTable[x] / 256;
		val.rgbGreen = left.rgbGreen + (right.rgbGreen - left.rgbGreen) * m_pTable[x] / 256;
		m_pScaleTab[i] = val;
	}
}

void CLinearScale::_Calculate()
{
	for (int i = 0; i < 8; i++) m_pTable[i] = i * 255 / 7;
}

void CLinearScale::DoFilter(BYTE* pSrc, int iXImg, int iYImg, int iXPos, int iYPos)
{
	CScaleFilter::DoFilter(pSrc, iXImg, iYImg, iXPos, iYPos);

	if (! m_pScaleTab) Init();
	int iXStep = 0x10000 / iXImg;
	int iYStep = 0xc000 / iYImg;

	int xd = 0, yd = 0;
	int mask1 = 0, mask2 = 0, mask = 0;
	BYTE* pFrom = NULL;
	DWORD* pTo = NULL;
	for (int y = 0; y < iYImg; y++)
	{
		pTo = m_pImg + iXImg * y;
		if ((yd & 0xff) < iYStep)
		{
			pFrom = pSrc + (yd & 0xff00);
			mask1 = (((((pFrom[0] << 3) + pFrom[0x100]) << 3) + pFrom[1]) << 3) + pFrom[0x101];
		}
		mask2 = (yd & 0x0e0) >> 2;
		yd += iYStep;

		xd = 0;
		BYTE* pTmp = pFrom;
		for (int x = 0; x < iXImg; x++)
		{
			mask = (mask1 << 6) + mask2 + ((xd & 0x0e0) >> 5);
			*(RGBQUAD*)pTo = m_pScaleTab[mask];
			pTo++;
			xd += iXStep;
			if ((xd & 0xff) < iXStep)
			{
				pFrom++;
				mask1 = (((mask1 << 3) + pFrom[1]) << 3) + pFrom[0x101];
				mask1 &= 0xfff;
			}
		}
		pFrom = pTmp;
	}
}

//--------------------------

void CBiquadraticScale::_Calculate()
{
	for (int i = 0; i < 8; i++) m_pTable[i] = int(255 * ((float)i / 7) * ((float)i / 7));
}

void CBicubicScale::_Calculate()
{
	for (int i = 0; i < 8; i++) m_pTable[i] = int(255 * ((float)i / 7) * ((float)i / 7) * ((float)i / 7));
}
