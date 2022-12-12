// DlgSEMLog.cpp : 实现文件
//
#include "stdafx.h"
#include "CustomTabCtrlDlgDynamicCreateChildWndApp.h"
#include "DlgSEMLog_GridHeaderSettings.h"


IMPLEMENT_DYNAMIC(CDlgSEMLog_GridHeaderSettings, CDialog)
CDlgSEMLog_GridHeaderSettings::CDlgSEMLog_GridHeaderSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSEMLog_GridHeaderSettings::IDD, pParent)
{
}

CDlgSEMLog_GridHeaderSettings::~CDlgSEMLog_GridHeaderSettings()
{
}


BEGIN_MESSAGE_MAP(CDlgSEMLog_GridHeaderSettings, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


BOOL CDlgSEMLog_GridHeaderSettings::OnInitDialog()
{
	CDialog::OnInitDialog();
	UpdateData(FALSE);
	return TRUE;
}




void CDlgSEMLog_GridHeaderSettings::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType,cx,cy);
}
