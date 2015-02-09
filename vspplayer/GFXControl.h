// GFXControl.h: interface for the CGFXControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GFXCONTROL_H__78057CFC_FA65_4946_B9BB_F6694956929C__INCLUDED_)
#define AFX_GFXCONTROL_H__78057CFC_FA65_4946_B9BB_F6694956929C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGFXControl  
{
public:
	CGFXControl();
	virtual ~CGFXControl();
	void DrawItem(int iItem, int iState, CWnd* pWnd);
	void DrawTime(CDC* pDC, int iFrame, int iDelay);
private:
	CBitmap m_cbOpen1;
	CBitmap m_cbOpen2;

	CBitmap m_cbPlay1;
	CBitmap m_cbPlay2;

	CBitmap m_cbStop1;
	CBitmap m_cbStop2;

	CBitmap m_cbInfo1;
	CBitmap m_cbInfo2;

	CBitmap m_cbSetup1;
	CBitmap m_cbSetup2;

	CBitmap m_cbAbout1;
	CBitmap m_cbAbout2;

	CBitmap m_cbOntop1;
	CBitmap m_cbOntop2;

	CBitmap m_cbMinimize1;
	CBitmap m_cbMinimize2;

	CBitmap m_cbMaximize1;
	CBitmap m_cbMaximize2;

	CBitmap m_cbClose1;
	CBitmap m_cbClose2;

	CBitmap m_cbDigit;

	int m_iLastControl;
};

#endif // !defined(AFX_GFXCONTROL_H__78057CFC_FA65_4946_B9BB_F6694956929C__INCLUDED_)
