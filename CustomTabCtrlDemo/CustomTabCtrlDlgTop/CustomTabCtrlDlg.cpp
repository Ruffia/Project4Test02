// CustomTabCtrlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CustomTabCtrlTopApp.h"
#include "CustomTabCtrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomTabCtrlDlg dialog

	
CCustomTabCtrlDlg::CCustomTabCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCustomTabCtrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCustomTabCtrlDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCustomTabCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomTabCtrlDlg)
	DDX_Control(pDX, IDC_PAGE_HOLDER, m_stPlaceHolder);
	DDX_Control(pDX, IDC_TAB, m_ctrlTab);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCustomTabCtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CCustomTabCtrlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
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

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_ctrlTab.SetDragCursors(AfxGetApp()->LoadCursor(IDC_CURSORMOVE),AfxGetApp()->LoadCursor(IDC_CURSORCOPY));
	m_ctrlTab.InsertItem(0,"SS_BLACKRECT");
	m_ctrlTab.SetItemData(0,SS_BLACKRECT);
	m_ctrlTab.InsertItem(1,"SS_GRAY");
	m_ctrlTab.SetItemData(1,SS_GRAYRECT);
	m_ctrlTab.InsertItem(2,"SS_WHITERECT");
	m_ctrlTab.SetItemData(2,SS_WHITERECT);
	m_ctrlTab.SetCurSel(0);
	
	m_ctrlTab.ModifyStyle(0,CTCS_EDITLABELS,0);
	m_ctrlTab.ModifyStyle(0,CTCS_AUTOHIDEBUTTONS,0);
	m_ctrlTab.ModifyStyle(0,CTCS_DRAGMOVE,0);
	m_ctrlTab.ModifyStyle(0,CTCS_CLOSEBUTTON,0);
	m_ctrlTab.ModifyStyle(0,CTCS_MULTIHIGHLIGHT,0);
	m_ctrlTab.ModifyStyle(0,CTCS_DRAGCOPY,0);
	m_ctrlTab.ModifyStyle(0,CTCS_TOP,0);

	LOGFONT lf = {15, 0, 0, 0, FW_NORMAL, 0, 0, 0,
		DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Courier"};

	m_ctrlTab.SetControlFont(lf, TRUE);

	CRect r;
	GetClientRect(r);
	_Resize(r.Width(),r.Height());
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCustomTabCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CCustomTabCtrlDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCustomTabCtrlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCustomTabCtrlDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	_Resize(cx,cy);
}

void CCustomTabCtrlDlg::_Resize(int cx, int cy)
{
	if(!m_ctrlTab.m_hWnd) return;

	int m = 15;
	int h = 25;
	CRect rBn(1114,63,1281,88);

	int nHolderPosition[Four] = {0}; 
	int nTabPosition[Four] = {0};
	if(m_ctrlTab.IsVertical() && m_ctrlTab.GetStyle()&CTCS_TOP) // left
	{
		nHolderPosition[Left] = m+h;
		nHolderPosition[Top] = m;
		nHolderPosition[Width] = cx-3*m-rBn.Width()-h;
		nHolderPosition[Height] = cy-2*m;

		nTabPosition[Left] = m;
		nTabPosition[Top] = m;
		nTabPosition[Width] = h;
		nTabPosition[Height] = cy-2*m;	
	}
	else if(m_ctrlTab.GetStyle()&CTCS_TOP) // top
	{
		nHolderPosition[Left] = m;
		nHolderPosition[Top] = h+m;
		nHolderPosition[Width] = cx-3*m-rBn.Width();
		nHolderPosition[Height] = cy-h-2*m;

		nTabPosition[Left] = m;
		nTabPosition[Top] = m;
		nTabPosition[Width] = cx-3*m-rBn.Width();
		nTabPosition[Height] = h;	
	}
	else if(m_ctrlTab.IsVertical()) // right
	{
		nHolderPosition[Left] = m;
		nHolderPosition[Top] = m;
		nHolderPosition[Width] = cx-3*m-rBn.Width()-h;
		nHolderPosition[Height] = cy-2*m;

		nTabPosition[Left] = m+cx-3*m-rBn.Width()-h;
		nTabPosition[Top] = m;
		nTabPosition[Width] = h;
		nTabPosition[Height] = cy-2*m;	
	}
	else // bottom
	{
		nHolderPosition[Left] = m;
		nHolderPosition[Top] = m;
		nHolderPosition[Width] = cx-3*m-rBn.Width();
		nHolderPosition[Height] = cy-h-2*m;
		
		nTabPosition[Left] = m;
		nTabPosition[Top] = cy-h-m;
		nTabPosition[Width] = cx-3*m-rBn.Width();
		nTabPosition[Height] = h;		
	}

	m_stPlaceHolder.MoveWindow(nHolderPosition[Left],nHolderPosition[Top],nHolderPosition[Width],nHolderPosition[Height]);
	m_ctrlTab.MoveWindow(nTabPosition[Left],nTabPosition[Top],nTabPosition[Width],nTabPosition[Height]);

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
	m_stPlaceHolder.ModifyStyle(SS_BLACKRECT|SS_GRAYRECT|SS_WHITERECT,((CTC_NMHDR*)pNMHDR)->lParam);
	m_stPlaceHolder.Invalidate();
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
		if(m_ctrlTab.DeleteItem(m_ctrlTab.GetCurSel())!=CTCERR_NOERROR)
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
				nInsNdx = m_ctrlTab.GetItemCount();
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
				m_ctrlTab.SetCurSel(((CTC_NMHDR*)pNMHDR)->nItem);
				nInsNdx = ((CTC_NMHDR*)pNMHDR)->nItem;
				menu.AppendMenu(MF_STRING,1,_T("Insert Item"));
				menu.AppendMenu(MF_STRING,2,_T("Delete Item"));
				menu.AppendMenu(MF_STRING,3,_T("Rename"));
			}
	
			CPoint pt(((CTC_NMHDR*)pNMHDR)->ptHitTest);
			m_ctrlTab.ClientToScreen(&pt);

			int nRet = menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, 
								pt.x, pt.y, this);
			switch(nRet)
			{
			case 1:
				{
					if(m_ctrlTab.InsertItem(nInsNdx,_T("New SS_WHITERECT Item"),SS_WHITERECT)<0)
						AfxMessageBox("InsertItem(...) failed.\nPossible errors:\n1. Item index out of range.");
				}
				break;
			case 2:
				{
					if(m_ctrlTab.DeleteItem(((CTC_NMHDR*)pNMHDR)->nItem)!=CTCERR_NOERROR)
						AfxMessageBox("DeleteItem(...) failed.\nPossible errors:\n1. Item index out of range.");
				}
				break;
			case 3:
				{
					if(m_ctrlTab.EditLabel(((CTC_NMHDR*)pNMHDR)->nItem)!=CTCERR_NOERROR)
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


void CCustomTabCtrlDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/) 
{
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
