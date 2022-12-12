#pragma once
#include <vector>
using namespace std;
#include "..\CustomTabCtrl.h"

class CCustomTabCtrlDlg;

class CMainDlg : public CDialog
{
public:
	CMainDlg(CWnd* pParent = NULL);
	~CMainDlg();
	enum { IDD = IDD_DIALOG_MAIN };
protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

private:
	void _Resize(int cx, int cy);
	CCustomTabCtrlDlg* m_pTabWnd;
};
