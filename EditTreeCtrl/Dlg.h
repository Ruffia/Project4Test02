// Dlg.h : header file
//

#if !defined(AFX_DLG_H__B66A74AE_1603_424F_9510_63BC4E74F0D5__INCLUDED_)
#define AFX_DLG_H__B66A74AE_1603_424F_9510_63BC4E74F0D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EditTreeCtrlEx.h"


class CTestTreeCtrl : public CEditTreeCtrlEx {
	protected:
		virtual void OnNewItem(HTREEITEM) {
					TRACE0("User created a new item.\n");
				}
};


/////////////////////////////////////////////////////////////////////////////
// CDlg dialog

class CDlg : public CDialog
{
	CImageList m_listTreeImages;

	// Construction
	public:
		CDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
		//{{AFX_DATA(CDlg)
	enum { IDD = IDD_ChildDialog_Tree };
		CTestTreeCtrl	m_ctrlTree;
	BOOL	m_bMultiSelect;
	//}}AFX_DATA

		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CDlg)
		protected:
		virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
		//}}AFX_VIRTUAL

	// Implementation
	protected:
		HICON m_hIcon;

		// Generated message map functions
		//{{AFX_MSG(CDlg)
		virtual BOOL OnInitDialog();
		afx_msg void OnPaint();
		afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnMultiSelect();
	//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__B66A74AE_1603_424F_9510_63BC4E74F0D5__INCLUDED_)
