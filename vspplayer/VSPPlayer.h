// VSPPlayer.h : main header file for the VSPPLAYER application
//

#if !defined(AFX_VSPPLAYER_H__FBAFCA21_0934_4DD4_AEF8_70FFD628A3D2__INCLUDED_)
#define AFX_VSPPLAYER_H__FBAFCA21_0934_4DD4_AEF8_70FFD628A3D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CVSPPlayerApp:
// See VSPPlayer.cpp for the implementation of this class
//

class CVSPPlayerApp : public CWinApp
{
public:
	CVSPPlayerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVSPPlayerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CVSPPlayerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VSPPLAYER_H__FBAFCA21_0934_4DD4_AEF8_70FFD628A3D2__INCLUDED_)
