#include "stdafx.h"
#include "CustomTabCtrlDlgDynamicCreateCrossTabApp.h"
#include "CustomTabCtrlDlg.h"
#include "DlgSEMLog_OperationQueryKeyWordSettings.h"
#include "DlgSEMLog_GridHeaderSettings.h"
#include "DlgSEMLog_PageB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CCustomTabCtrlDlg::CCustomTabCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomTabCtrlDlg::IDD, pParent),m_pTab(NULL),m_nCurSel(0)
{
}

CCustomTabCtrlDlg::~CCustomTabCtrlDlg()
{
	if(m_pTab)
	{
		delete m_pTab;
		m_pTab = NULL;
	}

	for (int i = 0; i < m_vPage.size();i++)
	{
		CDialog* pDlg = m_vPage[i];
		delete pDlg;
		pDlg = NULL;
	}

	m_vPage.clear();
}

void CCustomTabCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCustomTabCtrlDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_NOTIFY(CTCN_CLICK, IDC_TAB, OnLButtonClickedTab)
	ON_NOTIFY(CTCN_RCLICK, IDC_TAB, OnRButtonClickedTab)
	ON_NOTIFY(CTCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	ON_NOTIFY(CTCN_HIGHLIGHTCHANGE, IDC_TAB, OnHighlightchangeTab)
	ON_NOTIFY(CTCN_ITEMMOVE, IDC_TAB, OnMoveitemTab)
	ON_NOTIFY(CTCN_ITEMCOPY, IDC_TAB, OnCopyitemTab)
	ON_NOTIFY(CTCN_LABELUPDATE, IDC_TAB, OnLabelupdateTab)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDlg message handlers

BOOL CCustomTabCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	_CreateTabCtrl();


	
	return TRUE; 
}


void CCustomTabCtrlDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	_Resize(cx,cy);
}

void CCustomTabCtrlDlg::_Resize(int cx, int cy)
{
	if(!m_pTab) return; 	
	if(!m_pTab->m_hWnd) return;

	int nTabLeft = 5;
	int nTabTop = 5;
	int nTabItemHeight = 20;

	int nMarginWidth = 20;
	int nMarginHeight = 36;

	int nHolderPosition[Four] = {0}; 
	int nTabPosition[Four] = {0};

	nHolderPosition[Left] = nTabLeft + nTabItemHeight;
	nHolderPosition[Top] = nTabTop;
	nHolderPosition[Width] = cx - nMarginHeight;
	nHolderPosition[Height] = cy - nMarginWidth;

	nTabPosition[Left] = nTabLeft;
	nTabPosition[Top] = nTabTop;
	nTabPosition[Width] = nTabItemHeight;
	nTabPosition[Height] = cy - nMarginWidth;	


	for (int i = 0; i < m_vPage.size();i++)
	{
		CDialog* pPage = m_vPage[i];
		pPage->MoveWindow(nHolderPosition[Left],nHolderPosition[Top],nHolderPosition[Width],nHolderPosition[Height]);
	}

	m_pTab->MoveWindow(nTabPosition[Left],nTabPosition[Top],nTabPosition[Width],nTabPosition[Height]);
	RedrawWindow(NULL,NULL,RDW_ALLCHILDREN|RDW_ERASE|RDW_INVALIDATE);

}

void CCustomTabCtrlDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TRACE("Notify(CTCN_SELCHANGE): nItem(%d) pszText(\'%s\') lParam(%d) point(x=%d,y=%d) rect(l=%d,t=%d,r=%d,b=%d) bSelected(%d) bHighlighted(%d)\n",
				((CTC_NMHDR*)pNMHDR)->nItem,
				((CTC_NMHDR*)pNMHDR)->pszText,
				((CTC_NMHDR*)pNMHDR)->lParam,
				((CTC_NMHDR*)pNMHDR)->ptHitTest.x,
				((CTC_NMHDR*)pNMHDR)->ptHitTest.y,
				((CTC_NMHDR*)pNMHDR)->rItem.left,
				((CTC_NMHDR*)pNMHDR)->rItem.top,
				((CTC_NMHDR*)pNMHDR)->rItem.right,
				((CTC_NMHDR*)pNMHDR)->rItem.bottom,
				((CTC_NMHDR*)pNMHDR)->fSelected,
				((CTC_NMHDR*)pNMHDR)->fHighlighted);
	m_nCurSel = ((CTC_NMHDR*)pNMHDR)->nItem;
	_ShowPage(m_nCurSel);
	*pResult = 0;
}

void CCustomTabCtrlDlg::OnHighlightchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TRACE("Notify(CTCN_HIGHLIGHTCHANGE): nItem(%d) pszText(\'%s\') lParam(%d) point(x=%d,y=%d) rect(l=%d,t=%d,r=%d,b=%d) bSelected(%d) bHighlighted(%d)\n",
				((CTC_NMHDR*)pNMHDR)->nItem,
				((CTC_NMHDR*)pNMHDR)->pszText,
				((CTC_NMHDR*)pNMHDR)->lParam,
				((CTC_NMHDR*)pNMHDR)->ptHitTest.x,
				((CTC_NMHDR*)pNMHDR)->ptHitTest.y,
				((CTC_NMHDR*)pNMHDR)->rItem.left,
				((CTC_NMHDR*)pNMHDR)->rItem.top,
				((CTC_NMHDR*)pNMHDR)->rItem.right,
				((CTC_NMHDR*)pNMHDR)->rItem.bottom,
				((CTC_NMHDR*)pNMHDR)->fSelected,
				((CTC_NMHDR*)pNMHDR)->fHighlighted);
	

	*pResult = 0;
}

void CCustomTabCtrlDlg::OnLButtonClickedTab(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	switch(((CTC_NMHDR*)pNMHDR)->nItem)
	{
	case CTCHT_ONCLOSEBUTTON:
		TRACE("OnLButtonClicked: Close\n");
		if(m_pTab->DeleteItem(m_pTab->GetCurSel())!=CTCERR_NOERROR)
			AfxMessageBox("DeleteItem(...) failed.\nPossible errors:\n1. Item index out of range.");
		break;
	case CTCHT_ONFIRSTBUTTON:
		TRACE("OnLButtonClicked: First\n");
		break;
	case CTCHT_ONPREVBUTTON:
		TRACE("OnLButtonClicked: Prev\n");
		break;
	case CTCHT_ONNEXTBUTTON:
		TRACE("OnLButtonClicked: Next\n");
		break;
	case CTCHT_ONLASTBUTTON:
		TRACE("OnLButtonClicked: Last\n");
		break;
	case CTCHT_NOWHERE:
		TRACE("OnLButtonClicked: Nowhere\n");
		break;
	default:
		{
			TRACE("Notify(CTCN_CLICK): nItem(%d) pszText(\'%s\') lParam(%d) point(x=%d,y=%d) rect(l=%d,t=%d,r=%d,b=%d) bSelected(%d) bHighlighted(%d)\n",
				((CTC_NMHDR*)pNMHDR)->nItem,
				((CTC_NMHDR*)pNMHDR)->pszText,
				((CTC_NMHDR*)pNMHDR)->lParam,
				((CTC_NMHDR*)pNMHDR)->ptHitTest.x,
				((CTC_NMHDR*)pNMHDR)->ptHitTest.y,
				((CTC_NMHDR*)pNMHDR)->rItem.left,
				((CTC_NMHDR*)pNMHDR)->rItem.top,
				((CTC_NMHDR*)pNMHDR)->rItem.right,
				((CTC_NMHDR*)pNMHDR)->rItem.bottom,
				((CTC_NMHDR*)pNMHDR)->fSelected,
				((CTC_NMHDR*)pNMHDR)->fHighlighted);
		}
		break;
	}
	*pResult = 0;
}

void CCustomTabCtrlDlg::OnRButtonClickedTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	switch(((CTC_NMHDR*)pNMHDR)->nItem)
	{
	case CTCHT_ONCLOSEBUTTON:
		TRACE("OnLButtonClicked: Close\n");
		break;
	case CTCHT_ONFIRSTBUTTON:
		TRACE("OnLButtonClicked: First\n");
		break;
	case CTCHT_ONPREVBUTTON:
		TRACE("OnLButtonClicked: Prev\n");
		break;
	case CTCHT_ONNEXTBUTTON:
		TRACE("OnLButtonClicked: Next\n");
		break;
	case CTCHT_ONLASTBUTTON:
		TRACE("OnLButtonClicked: Last\n");
		break;
	default:
		{
			int nInsNdx;
			CMenu menu;
			menu.CreatePopupMenu();
			if(((CTC_NMHDR*)pNMHDR)->nItem==CTCHT_NOWHERE)
			{
				TRACE("OnLButtonClicked: Nowhere\n");
				nInsNdx = m_pTab->GetItemCount();
				menu.AppendMenu(MF_STRING,1,_T("Insert Item"));
				menu.AppendMenu(MF_STRING|MF_GRAYED,2,_T("Delete Item"));
				menu.AppendMenu(MF_STRING|MF_GRAYED,3,_T("Rename"));
			}
			else
			{
				TRACE("Notify(CTCN_RCLICK): nItem(%d) pszText(\'%s\') lParam(%d) point(x=%d,y=%d) rect(l=%d,t=%d,r=%d,b=%d) bSelected(%d) bHighlighted(%d)\n",
						((CTC_NMHDR*)pNMHDR)->nItem,
						((CTC_NMHDR*)pNMHDR)->pszText,
						((CTC_NMHDR*)pNMHDR)->lParam,
						((CTC_NMHDR*)pNMHDR)->ptHitTest.x,
						((CTC_NMHDR*)pNMHDR)->ptHitTest.y,
						((CTC_NMHDR*)pNMHDR)->rItem.left,
						((CTC_NMHDR*)pNMHDR)->rItem.top,
						((CTC_NMHDR*)pNMHDR)->rItem.right,
						((CTC_NMHDR*)pNMHDR)->rItem.bottom,
						((CTC_NMHDR*)pNMHDR)->fSelected,
						((CTC_NMHDR*)pNMHDR)->fHighlighted);
				m_pTab->SetCurSel(((CTC_NMHDR*)pNMHDR)->nItem);
				nInsNdx = ((CTC_NMHDR*)pNMHDR)->nItem;
				menu.AppendMenu(MF_STRING,1,_T("Insert Item"));
				menu.AppendMenu(MF_STRING,2,_T("Delete Item"));
				menu.AppendMenu(MF_STRING,3,_T("Rename"));
			}
	
			CPoint pt(((CTC_NMHDR*)pNMHDR)->ptHitTest);
			m_pTab->ClientToScreen(&pt);

			int nRet = menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, 
								pt.x, pt.y, this);
			switch(nRet)
			{
			case 1:
				{
					if(m_pTab->InsertItem(nInsNdx,_T("New SS_WHITERECT Item"),SS_WHITERECT)<0)
						AfxMessageBox("InsertItem(...) failed.\nPossible errors:\n1. Item index out of range.");
				}
				break;
			case 2:
				{
					if(m_pTab->DeleteItem(((CTC_NMHDR*)pNMHDR)->nItem)!=CTCERR_NOERROR)
						AfxMessageBox("DeleteItem(...) failed.\nPossible errors:\n1. Item index out of range.");
				}
				break;
			case 3:
				{
					if(m_pTab->EditLabel(((CTC_NMHDR*)pNMHDR)->nItem)!=CTCERR_NOERROR)
						AfxMessageBox("EditLabel(...) failed.\nPossible errors:\n1. Item index out of range.\n2. Item not selected.\n3. CTCS_EDITLABELS style not specified.");
				}
				break;
			}
		}
		break;
	}
	*pResult = 0;
}

void CCustomTabCtrlDlg::OnMoveitemTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TRACE("Notify(CTCN_ITEMMOVE): nItem(%d) pszText(\'%s\') lParam(%d) point(x=%d,y=%d) rect(l=%d,t=%d,r=%d,b=%d) bSelected(%d) bHighlighted(%d)\n",
						((CTC_NMHDR*)pNMHDR)->nItem,
						((CTC_NMHDR*)pNMHDR)->pszText,
						((CTC_NMHDR*)pNMHDR)->lParam,
						((CTC_NMHDR*)pNMHDR)->ptHitTest.x,
						((CTC_NMHDR*)pNMHDR)->ptHitTest.y,
						((CTC_NMHDR*)pNMHDR)->rItem.left,
						((CTC_NMHDR*)pNMHDR)->rItem.top,
						((CTC_NMHDR*)pNMHDR)->rItem.right,
						((CTC_NMHDR*)pNMHDR)->rItem.bottom,
						((CTC_NMHDR*)pNMHDR)->fSelected,
						((CTC_NMHDR*)pNMHDR)->fHighlighted);
	*pResult = 0;
}

void CCustomTabCtrlDlg::OnCopyitemTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TRACE("Notify(CTCN_ITEMCOPY): nItem(%d) pszText(\'%s\') lParam(%d) point(x=%d,y=%d) rect(l=%d,t=%d,r=%d,b=%d) bSelected(%d) bHighlighted(%d)\n",
						((CTC_NMHDR*)pNMHDR)->nItem,
						((CTC_NMHDR*)pNMHDR)->pszText,
						((CTC_NMHDR*)pNMHDR)->lParam,
						((CTC_NMHDR*)pNMHDR)->ptHitTest.x,
						((CTC_NMHDR*)pNMHDR)->ptHitTest.y,
						((CTC_NMHDR*)pNMHDR)->rItem.left,
						((CTC_NMHDR*)pNMHDR)->rItem.top,
						((CTC_NMHDR*)pNMHDR)->rItem.right,
						((CTC_NMHDR*)pNMHDR)->rItem.bottom,
						((CTC_NMHDR*)pNMHDR)->fSelected,
						((CTC_NMHDR*)pNMHDR)->fHighlighted);
	*pResult = 0;
}

void CCustomTabCtrlDlg::OnLabelupdateTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TRACE("Notify(CTCN_LABELUPDATE): nItem(%d) pszText(\'%s\') lParam(%d) point(x=%d,y=%d) rect(l=%d,t=%d,r=%d,b=%d) bSelected(%d) bHighlighted(%d)\n",
						((CTC_NMHDR*)pNMHDR)->nItem,
						((CTC_NMHDR*)pNMHDR)->pszText,
						((CTC_NMHDR*)pNMHDR)->lParam,
						((CTC_NMHDR*)pNMHDR)->ptHitTest.x,
						((CTC_NMHDR*)pNMHDR)->ptHitTest.y,
						((CTC_NMHDR*)pNMHDR)->rItem.left,
						((CTC_NMHDR*)pNMHDR)->rItem.top,
						((CTC_NMHDR*)pNMHDR)->rItem.right,
						((CTC_NMHDR*)pNMHDR)->rItem.bottom,
						((CTC_NMHDR*)pNMHDR)->fSelected,
						((CTC_NMHDR*)pNMHDR)->fHighlighted);
	if(CString(((CTC_NMHDR*)pNMHDR)->pszText).IsEmpty())
	{
		*pResult = 1; // Invalid label name
		AfxMessageBox("Invalid label name");
	}
	else
		*pResult = 0; // Label name OK
}

LPCTSTR CCustomTabCtrlDlg::GetTooltipText(int nStyle)
{
	static LPCTSTR s[] = {"Sets the static window style to SS_BLACKRECT",
						"Sets the static window style to SS_GRAYRECT",
						"Sets the static window style to SS_WHITERECT"};
	switch(nStyle)
	{
	case SS_BLACKRECT:
		return s[0];
	case SS_GRAYRECT:
		return s[1];
	case SS_WHITERECT:
		return s[2];
	}
	return NULL;
}

void CCustomTabCtrlDlg::_ShowPage(const int nCurPage)
{
	for (int i = 0; i < m_vPage.size();i++)
	{
		CDialog* pPage = m_vPage[i];
		if (!pPage) continue;
		if (nCurPage == i)
		{
			pPage->ShowWindow(SW_SHOW);
		}
		else
		{
			pPage->ShowWindow(SW_HIDE);
		}
	}
}


void CCustomTabCtrlDlg::_CreateTabCtrl()
{
	CRect rcClient;
	GetClientRect(rcClient);

	m_pTab = new CCustomTabCtrl;
	CRect rcTab(rcClient.left + 17,rcClient.top + 27,rcClient.Width() - 20,rcClient.Height() - 20);
	m_pTab->Create(WS_CHILD|WS_VISIBLE|CTCS_DRAGMOVE|CTCS_TOP|CTCS_EDITLABELS|CTCS_CLOSEBUTTON|CTCS_AUTOHIDEBUTTONS|CTCS_MULTIHIGHLIGHT|CTCS_DRAGCOPY|CTCS_LEFT,rcTab,this,IDC_TAB);
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
