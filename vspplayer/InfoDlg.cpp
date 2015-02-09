// InfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VSPPlayer.h"
#include "InfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg dialog


CInfoDlg::CInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfoDlg)
	DDX_Control(pDX, IDC_LIST2, m_clbValues);
	DDX_Control(pDX, IDC_LIST1, m_clbNames);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CInfoDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg message handlers

BOOL CInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_clbNames.AddString("Filename:");
	m_clbNames.AddString("Version:");
	m_clbNames.AddString("Clip:");
	m_clbNames.AddString("Author:");
	m_clbNames.AddString("Frames:");
	m_clbNames.AddString("Framerate:");
	m_clbNames.AddString("Duration:");
	m_clbNames.AddString("Filesize:");
	m_clbNames.AddString("Bitrate:");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
