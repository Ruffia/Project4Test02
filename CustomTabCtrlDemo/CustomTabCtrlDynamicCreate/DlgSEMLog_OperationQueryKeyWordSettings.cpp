// DlgSEMLog.cpp : 实现文件
//
#include "stdafx.h"
#include "CustomTabCtrlDlgDynamicCreateApp.h"
#include "DlgSEMLog_OperationQueryKeyWordSettings.h"



IMPLEMENT_DYNAMIC(CDlgSEMLog_OperationQueryKeyWordSettings, CDialog)

CDlgSEMLog_OperationQueryKeyWordSettings::CDlgSEMLog_OperationQueryKeyWordSettings(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSEMLog_OperationQueryKeyWordSettings::IDD, pParent)
{

}

CDlgSEMLog_OperationQueryKeyWordSettings::~CDlgSEMLog_OperationQueryKeyWordSettings()
{
}


BEGIN_MESSAGE_MAP(CDlgSEMLog_OperationQueryKeyWordSettings, CDialog)
	ON_WM_SIZE()	
END_MESSAGE_MAP()


BOOL CDlgSEMLog_OperationQueryKeyWordSettings::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}


void CDlgSEMLog_OperationQueryKeyWordSettings::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType,cx,cy);
}
