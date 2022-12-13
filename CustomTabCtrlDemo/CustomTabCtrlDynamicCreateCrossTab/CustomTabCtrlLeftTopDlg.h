#pragma once
#include "CustomTabCtrlDlg.h"

class CCustomTabCtrlLeftTopDlg : public CCustomTabCtrlDlg
{
public:
	CCustomTabCtrlLeftTopDlg(CWnd* pParent = NULL);

protected:
	virtual void _CreateTabCtrl();
	virtual void _Resize(int cx, int cy);
};
