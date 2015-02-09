#if !defined(AFX_SETUPDIALOG_H__338F54A0_00D1_4BFC_97F5_4A9D0BAA72E9__INCLUDED_)
#define AFX_SETUPDIALOG_H__338F54A0_00D1_4BFC_97F5_4A9D0BAA72E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetupDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetupDialog dialog

class CSetupDialog : public CDialog
{
// Construction
public:
	CSetupDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetupDialog)
	enum { IDD = IDD_SETUPDIALOG };
	CComboBox	m_ccbFilter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetupDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetupDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETUPDIALOG_H__338F54A0_00D1_4BFC_97F5_4A9D0BAA72E9__INCLUDED_)
