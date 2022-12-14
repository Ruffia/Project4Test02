// CustomTabCtrlDlg.h : header file
//

#if !defined(AFX_CUSTOMTABCTRLDLG_H__B07EA255_FBFF_47A2_BFBA_A8E170BD0FCC__INCLUDED_)
#define AFX_CUSTOMTABCTRLDLG_H__B07EA255_FBFF_47A2_BFBA_A8E170BD0FCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\CustomTabCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDlg dialog

class CCustomTabCtrlDlg : public CDialog
{
// Construction
public:
	CCustomTabCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomTabCtrlDlg)
	enum { IDD = IDD_CUSTOMTABCTRL_DIALOG };
	CStatic	m_stPlaceHolder;
	CCustomTabCtrl	m_ctrlTab;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomTabCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCustomTabCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	afx_msg void OnRadio5();
	afx_msg void OnRadio6();
	//}}AFX_MSG
	// Notify messages from CCustomTabCtrl
	afx_msg void OnLButtonClickedTab(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnRButtonClickedTab(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHighlightchangeTab(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnMoveitemTab(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnCopyitemTab(NMHDR* pNMHDR, LRESULT* pResult) ;
	afx_msg void OnLabelupdateTab(NMHDR* pNMHDR, LRESULT* pResult) ;
	DECLARE_MESSAGE_MAP()

private:
	void _Resize(int cx, int cy);
	LPCTSTR GetTooltipText(int nStyle);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMTABCTRLDLG_H__B07EA255_FBFF_47A2_BFBA_A8E170BD0FCC__INCLUDED_)
