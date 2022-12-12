// DlgSEMLog.cpp : 实现文件
//
#include "stdafx.h"
#include "CustomTabCtrlDlgDynamicCreateApp.h"
#include "DlgSEMLog_PageB.h"


IMPLEMENT_DYNAMIC(CDlgSEMLog_PageB, CDialog)
CDlgSEMLog_PageB::CDlgSEMLog_PageB(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSEMLog_PageB::IDD, pParent)
{
}

CDlgSEMLog_PageB::~CDlgSEMLog_PageB()
{
}


BEGIN_MESSAGE_MAP(CDlgSEMLog_PageB, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


BOOL CDlgSEMLog_PageB::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateData(FALSE);
	return TRUE;
}




void CDlgSEMLog_PageB::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType,cx,cy);
}
