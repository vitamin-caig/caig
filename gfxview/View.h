// View.h: interface for the CView class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEW_H__F937F2E6_DCD0_4D3E_9210_D270C044AF5C__INCLUDED_)
#define AFX_VIEW_H__F937F2E6_DCD0_4D3E_9210_D270C044AF5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CView  
{
public:
	CView(BYTE* pData, int iBytes);
	virtual ~CView() {delete[] m_pData; delete[] m_pBitmap; delete[] m_pScaled;};
	virtual int Animate();
	virtual void NextMode() {};
	virtual void PrewMode() {};
	virtual void Render();
	virtual void Draw(HDC hDC, int iXDest, int iYDest);
	virtual void Invalidate();
	virtual void Invert();
	virtual void Save(const char* szFileName);
protected:
	virtual void _Scale(int iXTo, int iYTo);
	virtual int _HasAnimation();
protected:
	int m_iPhase;
	int m_iMode;
	BYTE* m_pData;
	BITMAPINFO m_biBitmap;
	DWORD* m_pBitmap;

	BITMAPINFO m_biScaled;
	DWORD* m_pScaled;
};

class CScrView : public CView
{
public:
	CScrView(BYTE* pData);
	virtual ~CScrView() {};
	virtual int Animate();
	virtual void NextMode();
	virtual void PrewMode();
	virtual void Render();
};

class CDblView : public CView
{
public:
	CDblView(BYTE* pData);
	virtual ~CDblView() {};
	virtual void Render();
	virtual void Invert();
protected:
	virtual int _HasAnimation();
};

class CTriView : public CView
{
public:
	CTriView(BYTE* pData);
	virtual ~CTriView() {};
	virtual int Animate();
	virtual void Render();
	virtual void Invert();
protected:
	virtual int _HasAnimation();
};

class CFontView : public CView
{
public:
	CFontView(BYTE* pData);
	virtual ~CFontView() {};
	virtual int Animate();
protected:
	virtual int _HasAnimation();
};


class C8colView : public CView
{
public:
	C8colView(BYTE* pData);
	virtual ~C8colView() {};
	virtual void Render();
	virtual int Animate();
	virtual void Invert();
protected:
	virtual int _HasAnimation();
private:
	void _Depack(BYTE* pData);
};

class CLCView : public CView
{
public:
	CLCView(BYTE* pData);
	virtual ~CLCView() {};
private:
	void _Depack(BYTE* pData);
};

class CBitView : public CView
{
public:
	CBitView(BYTE* pData);
	virtual ~CBitView() {delete[] m_pSrc;};
	virtual void NextMode();
	virtual void PrewMode();
private:
	void _Depack(DWORD iSprite);
	BYTE* m_pSrc;
};

class CChunkView : public CView
{
public:
	CChunkView(BYTE* pData);
	virtual ~CChunkView() {delete[] m_pSrc;};
	virtual int Animate() {return 0;}
	virtual void NextMode();
	virtual void PrewMode();
protected:
	virtual int _HasAnimation();
protected:
	BYTE* m_pSrc;
private:
	void _Rot();
protected:
	void _Depack(BYTE* pData);
};

class CChunkUnpView : public CChunkView
{
public:
	CChunkUnpView(BYTE* pData);
	virtual ~CChunkUnpView() {};
};

class CMCView : public CView
{
public:
	CMCView(BYTE* pData);
	virtual ~CMCView() {};
	virtual void Render();
protected:
	virtual int _HasAnimation();
};

class CMCXView : public CView
{
public:
	CMCXView(BYTE* pData);
	virtual ~CMCXView() {};
	virtual void Render();
	virtual void Invert();
protected:
	virtual int _HasAnimation();
};

class CSpriteView : public CDblView
{
public:
	CSpriteView(BYTE* pData);
	virtual ~CSpriteView() {delete[] m_pSrc;};
	virtual void NextMode();
	virtual void PrewMode();
protected:
	virtual int _HasAnimation();
private:
	void _Depack(DWORD iSprite);
	BYTE* m_pSrc;
};

#endif // !defined(AFX_VIEW_H__F937F2E6_DCD0_4D3E_9210_D270C044AF5C__INCLUDED_)
