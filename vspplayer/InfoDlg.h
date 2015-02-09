#if !defined(AFX_INFODLG_H__6648EB6C_AB0B_4CDB_A398_92FA2D148F52__INCLUDED_)
#define AFX_INFODLG_H__6648EB6C_AB0B_4CDB_A398_92FA2D148F52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InfoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg dialog

class CInfoDlg : public CDialog
{
// Construction
public:
	CInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInfoDlg)
	enum { IDD = IDD_INFODIALOG };
	CListBox	m_clbValues;
	CListBox	m_clbNames;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInfoDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFODLG_H__6648EB6C_AB0B_4CDB_A398_92FA2D148F52__INCLUDED_)
