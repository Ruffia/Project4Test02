// DIALOG_FOLDERTREE.cpp : implementation file
//

#include "stdafx.h"
#include "sample.h"
#include "DIALOG_FOLDERTREE.h"

#include "sampleDlg.h"
#include "CFolderList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern DIALOG_FOLDERTREE* pFolderTreeDialog;
extern CSampleDlg* pMainDialog;

//extern CSampleDlg* pMainDialog;

DIALOG_FOLDERTREE::DIALOG_FOLDERTREE(CWnd* pParent /*=NULL*/)
	: CDialog(DIALOG_FOLDERTREE::IDD, pParent)
{
	//{{AFX_DATA_INIT(DIALOG_FOLDERTREE)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DIALOG_FOLDERTREE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DIALOG_FOLDERTREE)
	DDX_Control(pDX, IDC_TREE1, m_tree);
	//}}AFX_DATA_MAP
	pFolderTreeDialog=this;
	
	m_tree.Init();
	m_tree.SetState(&pMainDialog->m_state);
	m_tree.AddAllDrive();
}


BEGIN_MESSAGE_MAP(DIALOG_FOLDERTREE, CDialog)
	//{{AFX_MSG_MAP(DIALOG_FOLDERTREE)
	ON_BN_CLICKED(IDC_BUTTON1, OnLoad)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DIALOG_FOLDERTREE message handlers


void DIALOG_FOLDERTREE::OnLoad()
{
	CFolderList FolderList;
	if(!FolderList.LoadListFromFile("selectedfolder.ini"))
	AfxMessageBox("'selectedfolder.ini' doesn't exist or invalid file format");
	
	FolderList.AddFolderInTree(&pFolderTreeDialog->m_tree);
}