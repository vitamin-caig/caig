// ScaleFilter.h: interface for the CScaleFilter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCALEFILTER_H__17B37A6C_2D60_48DA_BD42_3C9616DA3709__INCLUDED_)
#define AFX_SCALEFILTER_H__17B37A6C_2D60_48DA_BD42_3C9616DA3709__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CScaleFilter
{
public:
	CScaleFilter();
	virtual ~CScaleFilter();

	virtual void DoFilter(BYTE* pSrc, int iXImg, int iYImg, int iXPos, int iYPos);
	void Show(CDC* pDC);

protected:
	DWORD* m_pImg;
	
	BITMAPINFO m_biBitmap;
	RGBQUAD m_rgbqPalette[7];

	int m_iXMax;
	int m_iYMax;

	int m_iXImg;
	int m_iYImg;
	int m_iXPos;
	int m_iYPos;
};



class CNearestScale : public CScaleFilter
{
public:
	CNearestScale() : CScaleFilter() {};

	virtual void DoFilter(BYTE* pSrc, int iXImg, int iYImg, int iXPos, int iYPos);
};



class CLinearScale : public CScaleFilter
{
public:
	CLinearScale();
	virtual ~CLinearScale();

	virtual void DoFilter(BYTE* pSrc, int iXImg, int iYImg, int iXPos, int iYPos);

protected:
	void Init();
	virtual void _Calculate();

protected:
	BYTE* m_pTable;
	RGBQUAD* m_pScaleTab;
};

class CBiquadraticScale : public CLinearScale
{
public:
	CBiquadraticScale() : CLinearScale() {}
	virtual ~CBiquadraticScale() {}

protected:
	virtual void _Calculate();
};

class CBicubicScale : public CLinearScale
{
public:
	CBicubicScale() {}
	virtual ~CBicubicScale() {}
protected:
	virtual void _Calculate();
};	

#endif // !defined(AFX_SCALEFILTER_H__17B37A6C_2D60_48DA_BD42_3C9616DA3709__INCLUDED_)
