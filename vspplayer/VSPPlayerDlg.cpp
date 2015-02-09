// VSPPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VSPPlayer.h"
#include "VSPPlayerDlg.h"
#include "SetupDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CVSPPlayerApp theApp;

#include "encode.h"


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSPPlayerDlg dialog

CVSPPlayerDlg::CVSPPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVSPPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVSPPlayerDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_cbBrush.CreateSolidBrush(0xe55500);

	m_pPlayer = new CVSPPlay;
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_iPlaying = 0;
	m_pInfoDlg = NULL;

}

CVSPPlayerDlg::~CVSPPlayerDlg()
{
	delete m_pPlayer;
}

void CVSPPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVSPPlayerDlg)
	DDX_Control(pDX, IDC_SLIDER1, m_cscPosition);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVSPPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CVSPPlayerDlg)
	ON_WM_NCHITTEST()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_PLPAUS, OnPlpaus)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_INFO, OnInfo)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_OPENFILE, OnOpenfile)
	ON_BN_CLICKED(IDC_CLOSING, OnClosing)
	ON_BN_CLICKED(IDC_MINIMIZING, OnMinimizing)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_ONTOP, OnOntop)
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_ABOUT, OnAbout)
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZING()
	ON_BN_CLICKED(IDC_MAXIMIZING, OnMaximizing)
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_WINDOWPOSCHANGED()
	ON_BN_CLICKED(IDC_SETUP, OnSetup)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVSPPlayerDlg message handlers

BOOL CVSPPlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	this->SetWindowText("VSP Player 0.31");

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CVSPPlayerDlg::OnOK()
{
}

void CVSPPlayerDlg::OnCancel()
{
	CDialog::OnCancel();
}

#define SIZE_BORDER 3

UINT CVSPPlayerDlg::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
CRect tRect;
CPoint cpPnt;

	GetWindowRect(&tRect);
	cpPnt = point - tRect.TopLeft();

	int iRes = 0;

	if (cpPnt.x < SIZE_BORDER) iRes = 1;
	if (cpPnt.x > (tRect.Width() - SIZE_BORDER)) iRes = 2;
	
	if (cpPnt.y < SIZE_BORDER) iRes += 4;
	if (cpPnt.y > (tRect.Height() - SIZE_BORDER)) iRes += 8;

	int iRess[] = {0, HTLEFT, HTRIGHT, 0, HTTOP, HTTOPLEFT, HTTOPRIGHT, 0,
					HTBOTTOM, HTBOTTOMLEFT, HTBOTTOMRIGHT};

	if (iRes) return iRess[iRes];

	if ((cpPnt.y < 19) || (cpPnt.y > tRect.Height() - 59)) 
		return HTCAPTION;
	else
		return CDialog::OnNcHitTest(point);
}


void CVSPPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVSPPlayerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDC* pDC = GetDC();

		m_pPlayer->DrawFrame(pDC);

		pDC->DeleteDC();

		pDC = GetDlgItem(IDC_TIME)->GetDC();
		m_cgControl.DrawTime(pDC, m_pPlayer->m_wFrame, m_pPlayer->m_svspfhHeader.m_bDelay);
		pDC->DeleteDC();
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVSPPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVSPPlayerDlg::OnOpenfile() 
{
	// TODO: Add your control notification handler code here
CString szFileName(' ', 256);

CFileDialog cfdDialog(TRUE, "*.*", szFileName,
					  OFN_NONETWORKBUTTON | OFN_NOTESTFILECREATE | OFN_NOVALIDATE,
					  "All supported formats|*.vsp;*.trd;*.scl||",
					  this);

//EnableWindow(FALSE);
if (cfdDialog.DoModal() == IDOK)
{
	KillTimer(1);
	if (! m_pPlayer->OpenFile(cfdDialog.GetPathName())) return;
	m_cscPosition.SetRangeMax(m_pPlayer->m_svspfhHeader.m_wFrames);
	SetTimer(1, 20 * m_pPlayer->m_svspfhHeader.m_bDelay, NULL);
	m_iPlaying = 1;
}
//EnableWindow();
}

void CVSPPlayerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if (! m_pPlayer->RenderFrame())
	{
		KillTimer(1);
		m_iPlaying = 0;
		m_pPlayer->Rewind();
		m_cscPosition.SetPos(0);
		Invalidate(FALSE);
		return;
	}

	Invalidate(FALSE);
	m_cscPosition.SetPos(m_pPlayer->GetFrame());

	CDialog::OnTimer(nIDEvent);
}

void CVSPPlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	m_pPlayer->GotoFrame(m_cscPosition.GetPos());
	Invalidate(FALSE);
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CVSPPlayerDlg::OnPlpaus() 
{
	// TODO: Add your control notification handler code here
	if (m_iPlaying)
		KillTimer(1);
	else
		SetTimer(1, 20 * m_pPlayer->m_svspfhHeader.m_bDelay, NULL);
	m_iPlaying = !m_iPlaying;
}

void CVSPPlayerDlg::OnStop() 
{
	// TODO: Add your control notification handler code here
	if (m_iPlaying)
	{
		KillTimer(1);
		m_pPlayer->Rewind();
		m_cscPosition.SetPos(0);
		m_iPlaying = 0;
		Invalidate(FALSE);
	}
}

void CVSPPlayerDlg::OnInfo() 
{
	// TODO: Add your control notification handler code here
if (! m_pInfoDlg)
{
	char szTmp[33];

	m_pInfoDlg = new CInfoDlg;
	m_pInfoDlg->Create(IDD_INFODIALOG);

	memcpy(szTmp, m_pPlayer->m_svspfhHeader.m_cFileName, 8);
	szTmp[8] = 0;
	m_pInfoDlg->m_clbValues.AddString(szTmp);

	sprintf(szTmp, "%i", m_pPlayer->m_svspfhHeader.m_bVersion);
	m_pInfoDlg->m_clbValues.AddString(szTmp);

	for (int i = 0; i < 32; i++)
		szTmp[i] = cEncTab[m_pPlayer->m_svspfhHeader.m_cClipName[i]];
	szTmp[32] = 0;
	m_pInfoDlg->m_clbValues.AddString(szTmp);

	for (i = 0; i < 32; i++)
		szTmp[i] = cEncTab[m_pPlayer->m_svspfhHeader.m_cClipAuthor[i]];
	szTmp[32] = 0;
	m_pInfoDlg->m_clbValues.AddString(szTmp);

	sprintf(szTmp, "%i", m_pPlayer->m_svspfhHeader.m_wFrames);
	m_pInfoDlg->m_clbValues.AddString(szTmp);

	sprintf(szTmp, "%.2f fps", 50.0f / m_pPlayer->m_svspfhHeader.m_bDelay);
	m_pInfoDlg->m_clbValues.AddString(szTmp);

	int iTime = m_pPlayer->m_svspfhHeader.m_bDelay * m_pPlayer->m_svspfhHeader.m_wFrames;
	sprintf(szTmp, "%i min  %i sec  %i frm", iTime / 3000, (iTime % 3000) / 50, iTime % 50);
	m_pInfoDlg->m_clbValues.AddString(szTmp);


	int iTmp = 0;
	for (i = 0; m_pPlayer->m_svspfhHeader.m_bBlockSize[i]; i++) iTmp += m_pPlayer->m_svspfhHeader.m_bBlockSize[i];
	sprintf(szTmp, "%i blocks (%.1f kbytes)", iTmp, (float)iTmp / 4);
	m_pInfoDlg->m_clbValues.AddString(szTmp);

	if (! iTime) iTime++;
	sprintf(szTmp, "%i bytes/sec", iTmp * 256 * 50 / iTime);
	m_pInfoDlg->m_clbValues.AddString(szTmp);

	m_pInfoDlg->ShowWindow(SW_SHOW);
	m_pInfoDlg->RunModalLoop();
	delete m_pInfoDlg;
	m_pInfoDlg = NULL;
}
}

void CVSPPlayerDlg::OnSetup() 
{
	// TODO: Add your control notification handler code here
	CSetupDialog* csd = new CSetupDialog;
	
	csd->Create(IDD_SETUPDIALOG);

	csd->ShowWindow(SW_SHOW);
	int iRes = m_pPlayer->GetFilter();
	csd->m_ccbFilter.SetCurSel(iRes);

	if (csd->RunModalLoop() == IDOK)
	{
		iRes = csd->m_ccbFilter.GetCurSel();
		m_pPlayer->SetFilter(iRes);
		theApp.WriteProfileInt("Render", "Filter", iRes);
		Invalidate(TRUE);
	}

	delete csd;
}




void CVSPPlayerDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if (m_pInfoDlg) m_pInfoDlg->SendMessage(WM_CLOSE);
//	delete m_pInfoDlg;
//	m_pInfoDlg = NULL;
	CDialog::OnClose();
}

HBRUSH CVSPPlayerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
//	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here

//	hbr = m_cbBrush;

	// TODO: Return a different brush if the default is not desired
	return m_cbBrush;
}


void CVSPPlayerDlg::OnClosing() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CVSPPlayerDlg::OnMinimizing() 
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
}

void CVSPPlayerDlg::OnMaximizing() 
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_SYSCOMMAND, IsZoomed() ? SC_RESTORE : SC_MAXIMIZE, 0);
	Invalidate();
}

void CVSPPlayerDlg::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default
CString	csName(' ', 256);
	
	UINT iRes = DragQueryFile(hDropInfo, 0, csName.GetBuffer(255), 255);

	if (iRes)
	{
		KillTimer(1);
		if (m_pPlayer->OpenFile(csName))
		{
			m_cscPosition.SetRangeMax(m_pPlayer->m_svspfhHeader.m_wFrames);
			SetTimer(1, 20 * m_pPlayer->m_svspfhHeader.m_bDelay, NULL);
			m_iPlaying = 1;
		}
	}
	CDialog::OnDropFiles(hDropInfo);
}

void CVSPPlayerDlg::OnOntop() 
{
	// TODO: Add your control notification handler code here
	DWORD dwStyl = GetExStyle() & WS_EX_TOPMOST;

	SetWindowPos(dwStyl ? &wndNoTopMost : &wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	CWnd* cBut = GetDlgItem(IDC_ONTOP);
	cBut->ModifyStyleEx(WS_EX_STATICEDGE, dwStyl ? 0 : WS_EX_STATICEDGE);
}

BOOL CVSPPlayerDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	
	int iRes = pWnd->GetDlgCtrlID();

	if (iRes)
		m_cgControl.DrawItem(0, 0, this);
	m_cgControl.DrawItem(iRes, 1, pWnd);
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CVSPPlayerDlg::OnAbout() 
{
	// TODO: Add your control notification handler code here
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
}



void CVSPPlayerDlg::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	lpMMI->ptMinTrackSize = CPoint(267, 269);
	CDialog::OnGetMinMaxInfo(lpMMI);
}

void CVSPPlayerDlg::OnSizing(UINT fwSide, LPRECT pRect) 
{
	CDialog::OnSizing(fwSide, pRect);
	
	// TODO: Add your message handler code here
	CRect crTmp(*pRect);
	GetDlgItem(IDC_CLOSING)->MoveWindow(crTmp.Width() - 22, 0, 16, 16);
	GetDlgItem(IDC_MAXIMIZING)->MoveWindow(crTmp.Width() - 39, 0, 16,16);
	GetDlgItem(IDC_MINIMIZING)->MoveWindow(crTmp.Width() - 57, 0, 16,16);
	GetDlgItem(IDC_TITLE)->MoveWindow(crTmp.Width() / 2 - 58, 0, 104, 16);

	GetDlgItem(IDC_OPENFILE)->MoveWindow(8, crTmp.Height() - 33, 24, 24);
	GetDlgItem(IDC_PLPAUS)->MoveWindow(38, crTmp.Height() - 33, 24, 24);
	GetDlgItem(IDC_STOP)->MoveWindow(68, crTmp.Height() - 33, 24, 24);
	GetDlgItem(IDC_INFO)->MoveWindow(crTmp.Width() - 72, crTmp.Height() - 33, 24, 24);
	GetDlgItem(IDC_SETUP)->MoveWindow(crTmp.Width() - 40, crTmp.Height() - 33, 24, 24);

	GetDlgItem(IDC_TIME)->MoveWindow(98, crTmp.Height() - 33, 68, 20);
	GetDlgItem(IDC_SLIDER1)->MoveWindow(8, crTmp.Height() - 58, crTmp.Width() - 19, 16);

	m_pPlayer->UpdateSize(crTmp.Width() - 11, crTmp.Height() - 77);
	Invalidate(FALSE);
}



void CVSPPlayerDlg::OnNcLButtonDblClk(UINT nHitTest, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CRect tRect;
	GetWindowRect(&tRect);
	if (point.y - tRect.left < 16) OnMaximizing();
//	CDialog::OnNcLButtonDblClk(nHitTest, point);
}

#define STICK_LIMIT 20

void CVSPPlayerDlg::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CDialog::OnWindowPosChanged(lpwndpos);
	
	// TODO: Add your message handler code here
	OnSizing(0, &CRect(0, 0, lpwndpos->cx, lpwndpos->cy));
}


int CVSPPlayerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	int iFilter = theApp.GetProfileInt("Render", "Filter", 0);
	m_pPlayer->SetFilter(iFilter);
	return 0;
}
