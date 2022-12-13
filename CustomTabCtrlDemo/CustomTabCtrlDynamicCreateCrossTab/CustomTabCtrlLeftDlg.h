#pragma once
#include "CustomTabCtrlDlg.h"

class CCustomTabCtrlLeftDlg : public CCustomTabCtrlDlg
{
public:
	CCustomTabCtrlLeftDlg(CWnd* pParent = NULL);

protected:
	virtual void _CreateTabCtrl();
	virtual void _Resize(int cx, int cy);
};
