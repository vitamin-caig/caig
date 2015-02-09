// GFXControl.cpp: implementation of the CGFXControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VSPPlayer.h"
#include "GFXControl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGFXControl::CGFXControl()
{
	m_cbOpen1.LoadBitmap(IDB_OPEN1);
	m_cbOpen2.LoadBitmap(IDB_OPEN2);

	m_cbPlay1.LoadBitmap(IDB_PLAY1);
	m_cbPlay2.LoadBitmap(IDB_PLAY2);

	m_cbStop1.LoadBitmap(IDB_STOP1);
	m_cbStop2.LoadBitmap(IDB_STOP2);

	m_cbInfo1.LoadBitmap(IDB_INFO1);
	m_cbInfo2.LoadBitmap(IDB_INFO2);

	m_cbSetup1.LoadBitmap(IDB_SETUP1);
	m_cbSetup2.LoadBitmap(IDB_SETUP2);

	m_cbAbout1.LoadBitmap(IDB_ABOUT1);
	m_cbAbout2.LoadBitmap(IDB_ABOUT2);

	m_cbOntop1.LoadBitmap(IDB_ONTOP1);
	m_cbOntop2.LoadBitmap(IDB_ONTOP2);

	m_cbMaximize1.LoadBitmap(IDB_MAXIMIZE1);
	m_cbMaximize2.LoadBitmap(IDB_MAXIMIZE2);

	m_cbMinimize1.LoadBitmap(IDB_MINIMIZE1);
	m_cbMinimize2.LoadBitmap(IDB_MINIMIZE2);

	m_cbClose1.LoadBitmap(IDB_CLOSE1);
	m_cbClose2.LoadBitmap(IDB_CLOSE2);
	
	m_cbDigit.LoadBitmap(IDB_DIGITS);

	m_iLastControl = 0;
}

CGFXControl::~CGFXControl()
{
	m_cbOpen1.DeleteObject();
	m_cbOpen2.DeleteObject();

	m_cbPlay1.DeleteObject();
	m_cbPlay2.DeleteObject();

	m_cbStop1.DeleteObject();
	m_cbStop2.DeleteObject();

	m_cbInfo1.DeleteObject();
	m_cbInfo2.DeleteObject();

	m_cbSetup1.DeleteObject();
	m_cbSetup2.DeleteObject();

	m_cbAbout1.DeleteObject();
	m_cbAbout2.DeleteObject();

	m_cbOntop1.DeleteObject();
	m_cbOntop2.DeleteObject();

	m_cbMinimize1.DeleteObject();
	m_cbMinimize2.DeleteObject();

	m_cbClose1.DeleteObject();
	m_cbClose2.DeleteObject();

	m_cbDigit.DeleteObject();
}


void CGFXControl::DrawItem(int iItem, int iState, CWnd* pWnd)
{
	if (m_iLastControl == iItem) return;
	switch (iItem)
	{
	case IDC_OPENFILE:
		((CStatic*)pWnd)->SetBitmap(iState ? (HBITMAP)m_cbOpen2 : (HBITMAP)m_cbOpen1);
		break;
	case IDC_PLPAUS:
		((CStatic*)pWnd)->SetBitmap(iState ? (HBITMAP)m_cbPlay2 : (HBITMAP)m_cbPlay1);
		break;
	case IDC_STOP:
		((CStatic*)pWnd)->SetBitmap(iState ? (HBITMAP)m_cbStop2 : (HBITMAP)m_cbStop1);
		break;
	case IDC_INFO:
		((CStatic*)pWnd)->SetBitmap(iState ? (HBITMAP)m_cbInfo2 : (HBITMAP)m_cbInfo1);
		break;
	case IDC_SETUP:
		((CStatic*)pWnd)->SetBitmap(iState ? (HBITMAP)m_cbSetup2 : (HBITMAP)m_cbSetup1);
		break;
	
	case IDC_ABOUT:
		((CStatic*)pWnd)->SetBitmap(iState ? (HBITMAP)m_cbAbout2 : (HBITMAP)m_cbAbout1);
		break;
	case IDC_ONTOP:
		((CStatic*)pWnd)->SetBitmap(iState ? (HBITMAP)m_cbOntop2 : (HBITMAP)m_cbOntop1);
		break;
	case IDC_MAXIMIZING:
		((CStatic*)pWnd)->SetBitmap(iState ? (HBITMAP)m_cbMaximize2 : (HBITMAP)m_cbMaximize1);
		break;
	case IDC_MINIMIZING:
		((CStatic*)pWnd)->SetBitmap(iState ? (HBITMAP)m_cbMinimize2 : (HBITMAP)m_cbMinimize1);
		break;
	case IDC_CLOSING:
		((CStatic*)pWnd)->SetBitmap(iState ? (HBITMAP)m_cbClose2 : (HBITMAP)m_cbClose1);
		break;

	case 0:
		int iTmp;
		iTmp = m_iLastControl;
		m_iLastControl = 0;
		DrawItem(iTmp, 0, pWnd->GetDlgItem(iTmp));
		break;
	default:
		break;
	}
	m_iLastControl = iItem;
}


void CGFXControl::DrawTime(CDC* pDC, int iFrame, int iDelay)
{
	if (! iDelay) iDelay++;
	if (iFrame == 0xffff) iFrame = 0;

	CDC tDC;
	tDC.CreateCompatibleDC(pDC);
	tDC.SelectObject(m_cbDigit);

	char szDig[9];
	int iTime = iFrame * iDelay;
	sprintf(szDig, "%.2i:%.2i:%.2i", iTime / 3000, (iTime % 3000) / 50, iTime % 50);
	for (iFrame = 0; iFrame < 8; iFrame++)
		pDC->BitBlt(iFrame * 8 + 1, 1, 8, 16, &tDC, 0, (szDig[iFrame] - 48) * 16, SRCCOPY);

	tDC.DeleteDC();
}