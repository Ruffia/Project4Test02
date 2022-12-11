// CustomTabCtrl.h : main header file for the CUSTOMTABCTRL application
//

#if !defined(AFX_CUSTOMTABCTRL_H__C215DE83_2402_4A4A_BCA3_E42272C5F3CD__INCLUDED_)
#define AFX_CUSTOMTABCTRL_H__C215DE83_2402_4A4A_BCA3_E42272C5F3CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlApp:
// See CustomTabCtrl.cpp for the implementation of this class
//

class CCustomTabCtrlApp : public CWinApp
{
public:
	CCustomTabCtrlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomTabCtrlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCustomTabCtrlApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMTABCTRL_H__C215DE83_2402_4A4A_BCA3_E42272C5F3CD__INCLUDED_)
