#if !defined(AFX_DIALOG_FOLDERLIST_H__8CBEDE32_0D39_49BA_A1F3_FC79E8DBA903__INCLUDED_)
#define AFX_DIALOG_FOLDERLIST_H__8CBEDE32_0D39_49BA_A1F3_FC79E8DBA903__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DIALOG_FOLDERLIST.h : header file
//

#include "CFolderList.h"

class DIALOG_FOLDERLIST : public CDialog
{
// Construction
public:
	DIALOG_FOLDERLIST(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DIALOG_FOLDERLIST)
	enum { IDD = IDD_DIALOG_FOLDERLIST };
	CListBox m_list;
	CButton m_save;
	//}}AFX_DATA
	CFolderList FolderList;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DIALOG_FOLDERLIST)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DIALOG_FOLDERLIST)
	afx_msg void OnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOG_FOLDERLIST_H__8CBEDE32_0D39_49BA_A1F3_FC79E8DBA903__INCLUDED_)
