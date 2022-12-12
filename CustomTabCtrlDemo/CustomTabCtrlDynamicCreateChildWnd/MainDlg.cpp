#include "stdafx.h"
#include "CustomTabCtrlDlgDynamicCreateChildWndApp.h"
#include "MainDlg.h"

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent)
{
}

CMainDlg::~CMainDlg()
{

}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainDlg message handlers

BOOL CMainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rcClient;
	GetClientRect(rcClient);

	_Resize(rcClient.Width(),rcClient.Height());
	return TRUE; 
}


void CMainDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	_Resize(cx,cy);
}

void CMainDlg::_Resize(int cx, int cy)
{
	return;

}
