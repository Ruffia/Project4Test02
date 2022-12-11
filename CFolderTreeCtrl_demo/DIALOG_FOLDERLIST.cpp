// DIALOG_FOLDERLIST.cpp : implementation file
//

#include "stdafx.h"
#include "sample.h"
#include "DIALOG_FOLDERLIST.h"
#include "DIALOG_FOLDERTREE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern DIALOG_FOLDERLIST* pFolderListDialog;
extern DIALOG_FOLDERTREE* pFolderTreeDialog;

DIALOG_FOLDERLIST::DIALOG_FOLDERLIST(CWnd* pParent /*=NULL*/)
	: CDialog(DIALOG_FOLDERLIST::IDD, pParent)
{
	//{{AFX_DATA_INIT(DIALOG_FOLDERLIST)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DIALOG_FOLDERLIST::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DIALOG_FOLDERLIST)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Control(pDX, IDC_BUTTON1, m_save);
	//}}AFX_DATA_MAP
	pFolderListDialog = this;
}


BEGIN_MESSAGE_MAP(DIALOG_FOLDERLIST, CDialog)
	//{{AFX_MSG_MAP(DIALOG_FOLDERLIST)
		ON_BN_CLICKED(IDC_BUTTON1, OnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DIALOG_FOLDERLIST message handlers

void DIALOG_FOLDERLIST::OnSave()
{
	CFolderList FolderList;
	FolderList.AddFolderFromTree(&pFolderTreeDialog->m_tree);
	FolderList.SaveListInFile("selectedfolder.ini");
	ShellExecute(NULL,NULL,"selectedfolder.ini",NULL,NULL,SW_SHOW);
}