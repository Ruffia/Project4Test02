#pragma once
#include "..\CustomTabCtrl.h"

class CCustomTabCtrlDlg : public CDialog
{
public:
	CCustomTabCtrlDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_CUSTOMTABCTRL_DIALOG };
	CStatic	m_stPlaceHolder;
	CCustomTabCtrl	m_ctrlTab;

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnSize(UINT nType, int cx, int cy);

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
