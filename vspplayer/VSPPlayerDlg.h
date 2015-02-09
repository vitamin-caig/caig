// VSPPlayerDlg.h : header file
//

#if !defined(AFX_VSPPLAYERDLG_H__FE4DA082_C466_4F6E_A4EE_C5167E647702__INCLUDED_)
#define AFX_VSPPLAYERDLG_H__FE4DA082_C466_4F6E_A4EE_C5167E647702__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VSPPLAY.h"
#include "InfoDlg.h"
#include "GFXControl.h"

/////////////////////////////////////////////////////////////////////////////
// CVSPPlayerDlg dialog

class CVSPPlayerDlg : public CDialog
{
// display data
	CBrush m_cbBrush;
	
	CGFXControl m_cgControl;

	int m_iPlaying;
	CVSPPlay* m_pPlayer;
	CInfoDlg* m_pInfoDlg;

// Construction
public:
	CVSPPlayerDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CVSPPlayerDlg();

// Dialog Data
	//{{AFX_DATA(CVSPPlayerDlg)
	enum { IDD = IDD_VSPPLAYER_DIALOG };
	CSliderCtrl	m_cscPosition;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVSPPlayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVSPPlayerDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPlpaus();
	afx_msg void OnStop();
	afx_msg void OnInfo();
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnOpenfile();
	afx_msg void OnClosing();
	afx_msg void OnMinimizing();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnOntop();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnAbout();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnMaximizing();
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnSetup();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSPPLAYERDLG_H__FE4DA082_C466_4F6E_A4EE_C5167E647702__INCLUDED_)
