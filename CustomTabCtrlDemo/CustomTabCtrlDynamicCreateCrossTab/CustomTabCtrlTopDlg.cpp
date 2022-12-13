#include "stdafx.h"
#include "CustomTabCtrlDlgDynamicCreateCrossTabApp.h"
#include "CustomTabCtrlTopDlg.h"
#include "DlgSEMLog_OperationQueryKeyWordSettings.h"
#include "DlgSEMLog_GridHeaderSettings.h"
#include "DlgSEMLog_PageB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CCustomTabCtrlTopDlg::CCustomTabCtrlTopDlg(CWnd* pParent)
	: CCustomTabCtrlDlg(pParent)
{
}


void CCustomTabCtrlTopDlg::_Resize(int cx, int cy)
{
	if(!m_pTab) return; 	
	if(!m_pTab->m_hWnd) return;

	int nTabLeft = 5;
	int nTabTop = 5;
	int nTabItemHeight = 25;

	int nMarginWidth = 20;
	int nMarginHeight = 36;

	int nHolderPosition[Four] = {0}; 
	int nTabPosition[Four] = {0};

	nTabPosition[Left] = nTabLeft;
	nTabPosition[Top] = nTabTop;
	nTabPosition[Width] = cx - nMarginWidth;
	nTabPosition[Height] = nTabItemHeight;	

	nHolderPosition[Left] = nTabLeft;
	nHolderPosition[Top] = nTabTop + nTabItemHeight;
	nHolderPosition[Width] = cx - nMarginWidth;
	nHolderPosition[Height] = cy - nMarginHeight;

	for (int i = 0; i < m_vPage.size();i++)
	{
		CDialog* pPage = m_vPage[i];
		pPage->MoveWindow(nHolderPosition[Left],nHolderPosition[Top],nHolderPosition[Width],nHolderPosition[Height]);
	}

	m_pTab->MoveWindow(nTabPosition[Left],nTabPosition[Top],nTabPosition[Width],nTabPosition[Height]);
	RedrawWindow(NULL,NULL,RDW_ALLCHILDREN|RDW_ERASE|RDW_INVALIDATE);

}


void CCustomTabCtrlTopDlg::_CreateTabCtrl()
{
	CRect rcClient;
	GetClientRect(rcClient);

	m_pTab = new CCustomTabCtrl;
	CRect rcTab(rcClient.left + 17,rcClient.top + 27,rcClient.Width() - 20,rcClient.Height() - 20);
	m_pTab->Create(WS_CHILD|WS_VISIBLE|CTCS_DRAGMOVE|CTCS_TOP|CTCS_EDITLABELS|CTCS_CLOSEBUTTON|CTCS_AUTOHIDEBUTTONS|CTCS_MULTIHIGHLIGHT|CTCS_DRAGCOPY|CTCS_TOP,rcTab,this,IDC_TAB);
	m_pTab->SetDragCursors(AfxGetApp()->LoadCursor(IDC_CURSORMOVE),AfxGetApp()->LoadCursor(IDC_CURSORCOPY));
	m_pTab->InsertItem(0,"SS_BLACKRECT");
	m_pTab->SetItemData(0,SS_BLACKRECT);
	m_pTab->InsertItem(1,"SS_GRAY");
	m_pTab->SetItemData(1,SS_GRAYRECT);
	m_pTab->InsertItem(2,"SS_WHITERECT");
	m_pTab->SetItemData(2,SS_WHITERECT);
	m_pTab->SetCurSel(0);

	CDlgSEMLog_OperationQueryKeyWordSettings* pDlgOperationKeyWord = new CDlgSEMLog_OperationQueryKeyWordSettings;
	pDlgOperationKeyWord->Create(CDlgSEMLog_OperationQueryKeyWordSettings::IDD, this);
	m_vPage.push_back(pDlgOperationKeyWord);

	CDlgSEMLog_GridHeaderSettings* pDlgGridHeader = new CDlgSEMLog_GridHeaderSettings;
	pDlgGridHeader->Create(CDlgSEMLog_GridHeaderSettings::IDD, this);
	m_vPage.push_back(pDlgGridHeader);

	CDlgSEMLog_PageB* pDlgGridHeader2 = new CDlgSEMLog_PageB;
	pDlgGridHeader2->Create(CDlgSEMLog_PageB::IDD, this);
	m_vPage.push_back(pDlgGridHeader2);

	m_nCurSel = 0;
	//ÏÔÊ¾³õÊ¼Ò³Ãæ
	_ShowPage(m_nCurSel);
	LOGFONT lf = {15, 0, 0, 0, FW_NORMAL, 0, 0, 0,
		DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Courier"};

	m_pTab->SetControlFont(lf, TRUE);

	_Resize(rcClient.Width(),rcClient.Height());
}
