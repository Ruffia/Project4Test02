#pragma once
#include "CustomTabCtrlDlg.h"

class CCustomTabCtrlTopDlg : public CCustomTabCtrlDlg
{
public:
	CCustomTabCtrlTopDlg(CWnd* pParent = NULL);

protected:
	virtual void _CreateTabCtrl();
	virtual void _Resize(int cx, int cy);
};
