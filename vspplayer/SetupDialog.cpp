// SetupDialog.cpp : implementation file
//

#include "stdafx.h"
#include "VSPPlayer.h"
#include "SetupDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetupDialog dialog


CSetupDialog::CSetupDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSetupDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetupDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSetupDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetupDialog)
	DDX_Control(pDX, IDC_COMBO1, m_ccbFilter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetupDialog, CDialog)
	//{{AFX_MSG_MAP(CSetupDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetupDialog message handlers

BOOL CSetupDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_ccbFilter.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
