#if !defined(AFX_DIALOG_FOLDERTREE_H__094AB34B_8185_41EA_80B4_0A273E878DC3__INCLUDED_)
#define AFX_DIALOG_FOLDERTREE_H__094AB34B_8185_41EA_80B4_0A273E878DC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DIALOG_FOLDERTREE.h : header file
//

#include "CFolderTreeCtrl.h"

class DIALOG_FOLDERTREE : public CDialog
{
// Construction
public:
	DIALOG_FOLDERTREE(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DIALOG_FOLDERTREE)
	enum { IDD = IDD_DIALOG_FOLDERTREE };
	CFolderTreeCtrl	m_tree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DIALOG_FOLDERTREE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DIALOG_FOLDERTREE)
	afx_msg void OnLoad();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_FOLDERTREE_H__094AB34B_8185_41EA_80B4_0A273E878DC3__INCLUDED_)
