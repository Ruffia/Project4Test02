// TreeTest.h : main header file for the TREETEST application
//

#if !defined(AFX_TREETEST_H__A37815E1_8983_47FE_ACD0_74648BCF3070__INCLUDED_)
#define AFX_TREETEST_H__A37815E1_8983_47FE_ACD0_74648BCF3070__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CApp:
// See TreeTest.cpp for the implementation of this class
//

class CApp : public CWinApp
{
public:
	CApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREETEST_H__A37815E1_8983_47FE_ACD0_74648BCF3070__INCLUDED_)
