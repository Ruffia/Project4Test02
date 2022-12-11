/******************************************************************/
/*** Class to get physical paths of all checked folders         ***/
/***                                                            ***/
/*** Use this class like you want,  it's free !                 ***/
/***                                                            ***/
/***                                            By Adrien Pinet ***/
/******************************************************************/

#include "stdafx.h"
#include "CFolderList.h"

#include <fstream>
using namespace std;

CFolderList::CFolderList()
{
	list = NULL;
	listSize = 0;
}

void CFolderList::Free()
{
	while(list)
	{
		SFolder* p = list->next;
		delete[] list->folderPathName;
		delete list;
		list = p;
	}
	
	list = NULL;
	listSize = 0;
}

CFolderList::CFolderList(CFolderTreeCtrl* p_tree)
{
	list = NULL;
	listSize = 0;
	AddFolderFromTree(p_tree);
}

CFolderList::~CFolderList()
{
	Free();
}

char* CFolderList::GetFolderPathName(uLong index)
{
	SFolder* temp = list;
	
	for(uLong i = 0;i<index;i++)
	temp = temp->next;
	
	return temp->folderPathName;
}

void CFolderList::AddFolderFromTree(CFolderTreeCtrl* p_tree)
{
	Free();

	this->p_tree = p_tree;
	AddSelectedFolderInList();
}

void CFolderList::AddFolderInTree(CFolderTreeCtrl* p_tree)
{
	SFolder* temp = list;

	for(uLong i = 0 ; i < listSize ; i++)
	{
		p_tree->SelectFolder(temp->folderPathName);
		temp = temp->next;
	}
}

int CFolderList::SaveListInFile(char filePathName[])
{
	ofstream ini(filePathName,ios::out);
	if(!ini) return 0;

	ini << "[CFolderList File]" << endl;
	ini << "num selected folder = " << listSize <<endl;

	SFolder* temp = list;

	for(uLong i = 0 ; i < listSize ; i++)
	{
		ini << temp->folderPathName << endl;;
		temp = temp->next;
	}

	ini.close();

	return 1;
}

int CFolderList::LoadListFromFile(char filePathName[])
{
	Free();
	
	ifstream ini(filePathName,ios::in);
	if(!ini) return 0;

	char temp[MAXPATH];

	ini.getline(temp,MAXPATH);
	temp[18] = 0;
	
	if(strcmp(temp,"[CFolderList File]"))
	return 0;

	ini.read(temp,22);
	temp[22] = 0;

	if(strcmp(temp,"num selected folder = "))
	return 0;

	ini.getline(temp,MAXPATH);

	listSize = atol(temp);

	for(uLong i = 0 ; i < listSize ; i++)
	{
		ini.getline(temp,MAXPATH);
		
		SFolder* p = new SFolder;
		p->folderPathName = new char[strlen(temp)+1];
		strcpy(p->folderPathName, temp);
		p->next = list;
		list = p;
	}

	ini.close();

	return 1;

}

uLong CFolderList::GetListSize()
{
	return listSize;
}

int CFolderList::GetCheck(HTREEITEM hItem)
{
	unsigned long state = p_tree->GetItemState(hItem,  0xFFFFFFFF);
	unsigned long mask = 0x00003000;
	state &= mask;// on mais les autres bits ?0;
	
	return (state>>12)-1;
}

int CFolderList::IsFolder1IsInFolder2(char folderPathName1[], char folderPathName2[])
{
	for(uLong i = 0;i<strlen(folderPathName2);i++)
	{
		if(folderPathName1[i] != folderPathName2[i])
		return 0;
	}

	return 1;
}

int CFolderList::IsInList(char folderPathName[])
{
	SFolder* temp = list;

	for(uLong i = 0;i<listSize;i++)
	{
		if(IsFolder1IsInFolder2(folderPathName, temp->folderPathName))
		return 1;

		temp = temp->next;
	}
	
	return 0;
}

void CFolderList::AddSelectedFolderInList()
{
	HTREEITEM hItem = p_tree->GetChildItem(TVI_ROOT);

	while(hItem)
	{
		AddSelectedFolderInList(hItem);
		hItem = p_tree->GetNextItem(hItem, TVGN_NEXT);
	}
}

void CFolderList::AddSelectedFolderInList(HTREEITEM currentFolder)
{
	char folderPathName[MAXPATH];

	if(GetCheck(currentFolder))
	{
		GetFolderPathName(currentFolder, folderPathName);
		
		if(!IsInList(folderPathName))
		{
			SFolder* p = new SFolder;
			p->folderPathName = new char[strlen(folderPathName)+1];
			strcpy(p->folderPathName, folderPathName);
			p->next = list;
			list = p;

			listSize++;
		}

		return;
	}

	currentFolder = p_tree->GetChildItem(currentFolder);

	while(currentFolder)
	{
		if(TVIS_BOLD & p_tree->GetItemState(currentFolder, TVIS_BOLD)) // optimisation
		AddSelectedFolderInList(currentFolder);

		currentFolder = p_tree->GetNextItem(currentFolder, TVGN_NEXT);
	}

}

void CFolderList::GetFolderPathName(HTREEITEM currentItem, char* folderPathName)
{
	folderPathName[0] = 0;

	char* buffer[1000];
	int count = 0;

	if(currentItem == TVI_ROOT)
	return;

	while(currentItem)
	{
		buffer[count] = new char[p_tree->GetItemText(currentItem).GetLength() + 1];
		strcpy(buffer[count], p_tree->GetItemText(currentItem).GetBuffer(MAXPATH));
		count++;

		currentItem = p_tree->GetParentItem(currentItem);
	}

	sprintf(folderPathName, "%c:\\", buffer[count - 1][0]);

	for(int i = count - 2 ; i >= 0 ; i--)
	{
		strcat(folderPathName, buffer[i]);
		strcat(folderPathName, "\\");
		delete[] buffer[i];
	}
}
