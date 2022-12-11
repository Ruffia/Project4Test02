/******************************************************************/
/*** Class to reprisent and select folders contain in a drive   ***/
/***                                                            ***/
/*** Use this class like you want, it's free !                  ***/
/***                                                            ***/
/***                                            By Adrien Pinet ***/
/******************************************************************/


#include "stdafx.h"
#include "CFolderTreeCtrl.h"
#include "resource.h"

#define IDM_EVENT				32000 // I think it's enough to be in peace
#define IDM_EVENT_COLLAPSE		IDM_EVENT + 1
#define IDM_EVENT_UNCOLLAPSE	IDM_EVENT + 2
#define IDM_EVENT_SELECTALL		IDM_EVENT + 3
#define IDM_EVENT_UNSELECTALL	IDM_EVENT + 4
#define IDM_EVENT_OPEN			IDM_EVENT + 5


BEGIN_MESSAGE_MAP(CFolderTreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CFolderTreeCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_UPDATE_COMMAND_UI(IDM_EVENT_OPEN,MenuEventOpen)
	ON_UPDATE_COMMAND_UI(IDM_EVENT_SELECTALL,MenuEventSelectAll)
	ON_UPDATE_COMMAND_UI(IDM_EVENT_UNSELECTALL,MenuEventUnSelectAll)
	
END_MESSAGE_MAP()

CFolderTreeCtrl::CFolderTreeCtrl()
{
	p_state = NULL;
}

CFolderTreeCtrl::~CFolderTreeCtrl()
{
	p_state = NULL;
	Menu.DestroyMenu();
}

void CFolderTreeCtrl::SetState(CEdit* p_state)
{
	this->p_state = p_state;
}

void CFolderTreeCtrl::Init()
{
	p_state = NULL;
	m_imageListFolder.Create( 16, 16, ILC_COLOR8, 0, 0);

	m_imageListFolder.Add(AfxGetApp()->LoadIcon(IDI_FOLDER_CLOSE));
	m_imageListFolder.Add(AfxGetApp()->LoadIcon(IDI_FOLDER_OPEN));
	m_imageListFolder.Add(AfxGetApp()->LoadIcon(IDI_DRIVE_CDROM));
	m_imageListFolder.Add(AfxGetApp()->LoadIcon(IDI_DRIVE_REMOVABLE));
	m_imageListFolder.Add(AfxGetApp()->LoadIcon(IDI_DRIVE_FLOPPY));
	m_imageListFolder.Add(AfxGetApp()->LoadIcon(IDI_DRIVE_FIXED));
		
	SetImageList(&m_imageListFolder, TVSIL_NORMAL);
}

void CFolderTreeCtrl::AddDrive(char drivePathName[])
{
	char newDrive[100], volumeName[100];
	
	if(GetVolumeName(drivePathName, volumeName))
	sprintf(newDrive, "%c: [%s]", drivePathName[0], volumeName);
	else
	sprintf(newDrive, "%c:", drivePathName[0]);
	

	DrawChildren(InsertChildFolder(newDrive, TVI_ROOT));
}

void CFolderTreeCtrl::AddAllDrive()
{
	uLong driveList = GetLogicalDrives();
	char drivePathName[] = " :\\";
	
	for(int i = 1 ; i < 32 ; i++)
	{
		if(0x01 & (driveList >> i))
		{
			drivePathName[0] = 'A' + i;
			AddDrive(drivePathName);
		}
	}
}

int CFolderTreeCtrl::IsExistChildBold(HTREEITEM hItem)
{
	hItem = GetChildItem(hItem);
	
	while(hItem)
	{
		if(TVIS_BOLD & GetItemState(hItem, TVIS_BOLD))
		return 1;

		hItem = GetNextItem(hItem, TVGN_NEXT);	
	}

	return 0;
}

void CFolderTreeCtrl::VerifBoldParents(HTREEITEM hItem)
{
	HTREEITEM hParentItem = hItem;

	while(hParentItem = GetParentItem(hParentItem))
	SetItemState(hParentItem, IsExistChildBold(hParentItem) ? TVIS_BOLD: 0, TVIS_BOLD);
}

int CFolderTreeCtrl::IsAllChildFull(HTREEITEM hItem)
{
	hItem = GetChildItem(hItem);

	while(hItem)
	{
		if(GetCheck(hItem) == 0)
		return 0;

		hItem = GetNextItem(hItem, TVGN_NEXT);	
	}

	return 1;
}

int CFolderTreeCtrl::IsAllChildEmpty(HTREEITEM hItem)
{
	hItem = GetChildItem(hItem);

	while(hItem)
	{
		if(GetCheck(hItem))
		return 0;

		hItem = GetNextItem(hItem, TVGN_NEXT);	
	}

	return 1;
}

void CFolderTreeCtrl::VerifFullParents(HTREEITEM hItem)
{
	HTREEITEM hParentItem = hItem;
	while(hParentItem = GetParentItem(hParentItem))
	{
		if(IsAllChildFull(hParentItem))
		SetItemFull(hParentItem);
		else
		SetItemEmpty(hParentItem);
	}
}

int CFolderTreeCtrl::GetCheck(HTREEITEM hItem)
{
	unsigned long state = GetItemState(hItem, 0xFFFFFFFF);
	unsigned long mask = 0x00003000;
	state &= mask;// on mais les autres bits ?0;
	
	return (state>>12)-1;
}

void CFolderTreeCtrl::SetItemEmpty(HTREEITEM hItem)
{
	unsigned long state = GetItemState(hItem, 0xFFFFFFFF);
	unsigned long mask = 0x00003000^0xFFFFFFFF;
	state &= mask;// on mais les 2 bits ?0;
	state |= 4096;
	
	SetItemState(hItem, state, 0xFFFFFFFF);
	SetItemState(hItem, false ? TVIS_BOLD: 0, TVIS_BOLD);
}

void CFolderTreeCtrl::SetItemFull(HTREEITEM hItem)
{
	unsigned long state = GetItemState(hItem, 0xFFFFFFFF);
	unsigned long mask = 0x00003000^0xFFFFFFFF;
	state &= mask;// on mais les 2 bits ?0;
	state |= 8192;

	SetItemState(hItem, state, 0xFFFFFFFF);
	SetItemState(hItem, true ? TVIS_BOLD: 0, TVIS_BOLD);
}

void CFolderTreeCtrl::SetItemAndChildrenEmpty(HTREEITEM hItem)
{
	SetItemEmpty(hItem);
	HTREEITEM hChildItem = GetChildItem(hItem);
	
	while(hChildItem)
	{
		SetItemEmpty(hChildItem);
		SetItemAndChildrenEmpty(hChildItem);

		hChildItem = GetNextItem(hChildItem, TVGN_NEXT);
	}
}

void CFolderTreeCtrl::SetItemAndChildrenFull(HTREEITEM hItem)
{
	SetItemFull(hItem);
	HTREEITEM hChildItem = GetChildItem(hItem);

	while(hChildItem)
	{
		SetItemFull(hChildItem);
		SetItemAndChildrenFull(hChildItem);

		hChildItem = GetNextItem(hChildItem, TVGN_NEXT);
	}
}

void CFolderTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	UINT uFlags = 0;
	HTREEITEM hItem = HitTest(point, &uFlags);
	
	if(!hItem)
	return;
	
	SelectItem(hItem);
	SetFocus();
	OnSelchangedTree();

	if(uFlags & TVHT_ONITEMSTATEICON)
	{
		if(GetCheck(hItem))
		SetItemAndChildrenEmpty(hItem);
		else
		SetItemAndChildrenFull(hItem);
		
		VerifFullParents(hItem);
		VerifBoldParents(hItem);

		DrawNumSelectedFolder();
		return;
	}

	Expand(hItem, TVE_TOGGLE);
}

void CFolderTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	UINT uFlags = 0;
	HTREEITEM hItem = HitTest(point, &uFlags);
	
	if(!hItem)
	return;
	
	SelectItem(hItem);
	SetFocus();
	OnSelchangedTree();

	DrawContextMenu(hItem, point);
}

void CFolderTreeCtrl::GetFolderPathName(HTREEITEM currentItem, char* folderPathName)
{
	folderPathName[0] = 0;

	char* buffer[1000];
	int count = 0;

	if(currentItem == TVI_ROOT)
	return;

	while(currentItem)
	{
		buffer[count] = new char[GetItemText(currentItem).GetLength() + 1];
		strcpy(buffer[count], GetItemText(currentItem).GetBuffer(MAXPATH));
		count++;

		currentItem = GetParentItem(currentItem);
	}

	sprintf(folderPathName, "%c:\\", buffer[count - 1][0]);

	for(int i = count-2 ; i >= 0 ; i--)
	{
		strcat(folderPathName, buffer[i]);
		strcat(folderPathName, "\\");
		delete[] buffer[i];
	}
}

int CFolderTreeCtrl::IsValidFolder(char folderPathName[])
{
	// I think it's not the best method but it works !
	char oldCurrentDirectory[MAXPATH];
	GetCurrentDirectory(MAXPATH, oldCurrentDirectory);

	if(!SetCurrentDirectory(folderPathName))
	{
		SetCurrentDirectory(oldCurrentDirectory);
		return 0;
	}

	SetCurrentDirectory(oldCurrentDirectory);
	return 1;
}

void CFolderTreeCtrl::DrawChildren(HTREEITEM parentItem)
{
	WIN32_FIND_DATA Find;
	HANDLE		hFind;
	char parentFolderPathName[MAXPATH];
	char TEMP[MAXPATH];

	GetFolderPathName(parentItem, parentFolderPathName);

	if(parentFolderPathName[strlen(parentFolderPathName) - 1] != '\\')
	strcat(parentFolderPathName, "\\");

	sprintf(TEMP, "%s*", parentFolderPathName);
	hFind = FindFirstFile(TEMP, &Find);

	char currentFolderPathName[MAXPATH];
	
	while(hFind)
	{
		sprintf(currentFolderPathName, "%s%s", parentFolderPathName, Find.cFileName);

		if(IsValidFolder(currentFolderPathName) && strcmp(Find.cFileName, ".") != 0 && strcmp(Find.cFileName, "..") != 0)
		{

			InsertChildFolder(Find.cFileName, parentItem);

			if(GetCheck(parentItem))
			SetItemAndChildrenFull(parentItem);
		}

		if(!FindNextFile(hFind, &Find))
		return;
	}
}

int CFolderTreeCtrl::HaveChildren(char parentFolderPathName[])
{
	WIN32_FIND_DATA Find;
	HANDLE		hFind;
	char TEMP[MAXPATH];

	if(parentFolderPathName[strlen(parentFolderPathName)-1] != '\\')
	strcat(parentFolderPathName, "\\");

	sprintf(TEMP, "%s*", parentFolderPathName);
	hFind = FindFirstFile(TEMP, &Find);

	char currentFolderPathName[MAXPATH];

	while(hFind)
	{
		sprintf(currentFolderPathName, "%s%s", parentFolderPathName, Find.cFileName);

		if(IsValidFolder(currentFolderPathName) && strcmp(Find.cFileName, ".") != 0 && strcmp(Find.cFileName, "..") != 0)
		return 1;

		if(!FindNextFile(hFind, &Find))
		return 0;
	}

	return 0;
}

void CFolderTreeCtrl::OnSelchangedTree() 
{
	HTREEITEM hItem = GetSelectedItem();
	DrawChildren(hItem);
	
	DrawNumSelectedFolder();
}

void CFolderTreeCtrl::GetNumSelectedFolder(HTREEITEM currentItem, uLong* numSelectedFolder)
{
	if(GetCheck(currentItem))
	{
		(*numSelectedFolder)++;
		return;
	}
	
	HTREEITEM hChildItem = GetChildItem(currentItem);

	while(hChildItem)
	{
		if(TVIS_BOLD & GetItemState(hChildItem, TVIS_BOLD))
		GetNumSelectedFolder(hChildItem, numSelectedFolder);

		hChildItem = GetNextItem(hChildItem, TVGN_NEXT);
	}
}

uLong CFolderTreeCtrl::GetNumSelectedFolder()
{
	uLong numSelectedFolder = 0;
	HTREEITEM hChildItem = GetChildItem(TVI_ROOT);

	while(hChildItem)
	{
		if(TVIS_BOLD & GetItemState(hChildItem, TVIS_BOLD))
		GetNumSelectedFolder(hChildItem, &numSelectedFolder);

		hChildItem = GetNextItem(hChildItem, TVGN_NEXT);
	}

	return numSelectedFolder;
}

void CFolderTreeCtrl::DrawNumSelectedFolder()
{
	if(!p_state)
	return;

	char sNumSelectedFolder[100];
	sprintf(sNumSelectedFolder, "%d Selected Folder(s)", GetNumSelectedFolder());
	p_state->SetWindowText(sNumSelectedFolder);
}

void CFolderTreeCtrl::SelectFolder(char folderPathName[])
{
	char folderName[100];
	int deep = GetDeepFolderPathName(folderPathName);
	HTREEITEM parentItem = TVI_ROOT;

	for(int i = 0 ; i < deep ; i++)
	{
		CutFolderPathName(folderPathName, i, folderName);
		parentItem = InsertChildFolder(folderName, parentItem);
		DrawChildren(parentItem);
	}

	SetItemAndChildrenFull(parentItem);

	VerifFullParents(parentItem);
	VerifBoldParents(parentItem);

	DrawNumSelectedFolder();
}

int CFolderTreeCtrl::GetDeepFolderPathName(char folderPathName[])
{
	int deep = 0;

	for(int i = 0 ; folderPathName[i] ; i++)
		if(folderPathName[i] == '\\')
		deep++;

	return deep;
}



void CFolderTreeCtrl::CutFolderPathName(char folderPathName[], int deep, char folderName[])
{
	int start = 0, currentDeep = 0;
	
	while(currentDeep < deep)
	{
		if(folderPathName[start++] == '\\')
		currentDeep++;	
	}

	int k = 0;
	for(int i = start ; folderPathName[i] != '\\' ; i++)
	folderName[k++] = folderPathName[i];

	folderName[k] = 0;
}

HTREEITEM CFolderTreeCtrl::InsertChildFolder(char childFolderName[], HTREEITEM parentItem)
{
	/* We search if it already exists */
	HTREEITEM pCurrentItem = GetChildItem(parentItem);

	while(pCurrentItem)
	{
		if(strcmp(childFolderName, GetItemText(pCurrentItem).GetBuffer(100)) == 0)
		return pCurrentItem;
	
		pCurrentItem = GetNextItem(pCurrentItem, TVGN_NEXT);
	}

	pCurrentItem = NULL;

	/* We looking for if the folder have children */
	char parentFolderPathName[MAXPATH];
	GetFolderPathName(parentItem, parentFolderPathName);
	strcat(parentFolderPathName, childFolderName);
	int haveChildren = HaveChildren(parentFolderPathName);

	/* Sinon on l'insert */
	if(parentItem == TVI_ROOT)
	{
		if(GetDriveType(childFolderName) == DRIVE_FIXED)
		pCurrentItem = InsertItem(childFolderName, 5, 5, parentItem, TVI_LAST, haveChildren);
		
		if(GetDriveType(childFolderName) == DRIVE_CDROM)
		pCurrentItem = InsertItem(childFolderName, 2, 2, parentItem, TVI_LAST, haveChildren);
	
		if(GetDriveType(childFolderName) == DRIVE_REMOVABLE && childFolderName[0]  ==  'A')
		pCurrentItem = InsertItem(childFolderName, 4, 4, parentItem, TVI_LAST, haveChildren);
		
		if(GetDriveType(childFolderName) == DRIVE_REMOVABLE && childFolderName[0] != 'A')
		pCurrentItem = InsertItem(childFolderName, 3, 3, parentItem, TVI_LAST, haveChildren);
		
		if(pCurrentItem  == NULL)
		pCurrentItem = InsertItem(childFolderName, 5, 5, parentItem, TVI_LAST, haveChildren);
	}
	else
	pCurrentItem = InsertItem(childFolderName, 0, 1, parentItem, TVI_LAST, haveChildren);

	return pCurrentItem;
}

HTREEITEM CFolderTreeCtrl::InsertItem(char lpszItem[], int nImage, int nSelectedIamage, HTREEITEM hParent, HTREEITEM hInsertAfter, int haveChildren)
{
	if(!haveChildren)
	return CTreeCtrl::InsertItem(lpszItem, nImage, nSelectedIamage, hParent, hInsertAfter);

	TV_INSERTSTRUCT tvis;

	ZeroMemory(&tvis, sizeof(TV_INSERTSTRUCT));
	tvis.hParent			 = hParent;
	tvis.hInsertAfter		 = TVI_LAST;
	tvis.item.mask			 = TVIF_CHILDREN|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT;
	tvis.item.pszText		 = lpszItem;
	tvis.item.iImage		 = nImage;
	tvis.item.iSelectedImage = nSelectedIamage;
	tvis.item.cChildren		 = TRUE;
		
	return CTreeCtrl::InsertItem(&tvis);
}


void CFolderTreeCtrl::DrawContextMenu(HTREEITEM currentItem, CPoint pos)
{
	Menu.DestroyMenu();
	Menu.CreatePopupMenu();

	char itemText[100];

	if(GetParentItem(currentItem) == NULL)
	sprintf(itemText,"                           Display Disk %c                            ", GetItemText(currentItem).GetBuffer(100)[0]);
	else
	sprintf(itemText,"                           Display Folder %s                            ", GetItemText(currentItem).GetBuffer(100));
	
	Menu.AppendMenu(MF_STRING, IDM_EVENT_OPEN, itemText);
	Menu.AppendMenu(MF_SEPARATOR);
	
	if(!GetCheck(currentItem))
	Menu.AppendMenu(MF_STRING , IDM_EVENT_SELECTALL, "Select this folder and all SubFolder");
	else
	Menu.AppendMenu(MF_STRING , IDM_EVENT_UNSELECTALL, "Deselect this folder and all SubFolder");
	
	Menu.AppendMenu(MF_SEPARATOR);
	
	if(IsExistChildBold(currentItem))
	InsertSubFolderSelectedInMenu(currentItem);
	else
	Menu.AppendMenu(MF_STRING, 0, "0 Subfolder Selected");

	CRect rect;
	this->GetWindowRect(&rect);
	Menu.TrackPopupMenu(TPM_LEFTALIGN, rect.left + pos.x, rect.top + pos.y, this);
}

void CFolderTreeCtrl::InsertSubFolderSelectedInMenu(HTREEITEM currentItem)
{
	currentItem = GetChildItem(currentItem);
	
	while(currentItem)
	{
		if(GetCheck(currentItem))
		{
			char folderPathName[MAXPATH];
			GetFolderPathName(currentItem,folderPathName);
			Menu.AppendMenu(MF_STRING, IDM_EVENT, folderPathName);
		}

		InsertSubFolderSelectedInMenu(currentItem);
		currentItem = GetNextItem(currentItem, TVGN_NEXT);
	}
}

void CFolderTreeCtrl::MenuEventOpen(CCmdUI* pCmdUI)
{
	char folderPathName[MAXPATH];
	GetFolderPathName(GetSelectedItem(), folderPathName);
	ShellExecute(NULL,NULL,folderPathName,NULL,NULL,SW_SHOW);
}

void CFolderTreeCtrl::MenuEventSelectAll(CCmdUI* pCmdUI)
{
	HTREEITEM currentItem = GetSelectedItem();
	SetItemAndChildrenFull(currentItem);
	
	VerifFullParents(currentItem);
	VerifBoldParents(currentItem);

	DrawNumSelectedFolder();
}

void CFolderTreeCtrl::MenuEventUnSelectAll(CCmdUI* pCmdUI)
{
	HTREEITEM currentItem = GetSelectedItem();
	SetItemAndChildrenEmpty(currentItem);

	VerifFullParents(currentItem);
	VerifBoldParents(currentItem);

	DrawNumSelectedFolder();
}

int CFolderTreeCtrl::GetVolumeName(char rootDrive[], char volumeName[])
{
	return GetVolumeInformation(rootDrive, volumeName, MAXPATH, NULL, NULL, NULL, NULL, 0) && strlen(volumeName) != 0;
}