#include "stdafx.h"
#include "CustomTabCtrlDlgDynamicCreateChildWndApp.h"
#include "MainDlg.h"
#include "CustomTabCtrlDlg.h"

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainDlg::IDD, pParent),m_pTabWnd(NULL)
{
}

CMainDlg::~CMainDlg()
{
	if (m_pTabWnd)
	{
		delete m_pTabWnd;
		m_pTabWnd = NULL;
	}
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

	CWnd* pTabWnd = GetDlgItem(IDC_STATIC_TAB);

	m_pTabWnd = new CCustomTabCtrlDlg;
	m_pTabWnd->Create(CCustomTabCtrlDlg::IDD,pTabWnd);

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
	CRect rcTab;
	CWnd* pWnd = GetDlgItem(IDC_STATIC_TAB);
	if (!pWnd || !pWnd->m_hWnd) return;

	pWnd->GetClientRect(rcTab);
	m_pTabWnd->MoveWindow(rcTab.left,rcTab.top,rcTab.Width(),rcTab.Height());
}
