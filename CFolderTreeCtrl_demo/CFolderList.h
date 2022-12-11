/******************************************************************/
/*** Class to get physical paths of all checked folders         ***/
/***                                                            ***/
/*** Use this class like you want, it's free !                  ***/
/***                                                            ***/
/***                                            By Adrien Pinet ***/
/******************************************************************/


#ifndef __CFOLDERLIST_H__
#define __CFOLDERLIST_H__

#include "CFolderTreeCtrl.h"
typedef unsigned long uLong;

struct SFolder
{
	char* folderPathName;
	SFolder* next;
};

class CFolderList
{
public:
	CFolderList();
	CFolderList(CFolderTreeCtrl* p_tree);
	virtual ~CFolderList();

	void AddFolderFromTree(CFolderTreeCtrl* p_tree); // load selected item/folder from a CFolderTreeList in the current list
	void AddFolderInTree(CFolderTreeCtrl* p_tree); // load selected item/folder from a the current list in the CFolderTreeList

	int SaveListInFile(char filePathName[]);
	int LoadListFromFile(char filePathName[]);

	char* GetFolderPathName(uLong index); // return a char pointer of a physical path from the list
	uLong GetListSize(); // return the list size 

private:
	void Free();
	void AddSelectedFolderInList();
	void AddSelectedFolderInList(HTREEITEM currentFolder);

	int GetCheck(HTREEITEM hItem);
	int IsInList(char folderPathName[]);
	int IsFolder1IsInFolder2(char folderPathName1[],char folderPathName2[]);
	void GetFolderPathName(HTREEITEM currentItem,char* folderPathName);

private:
	CFolderTreeCtrl* p_tree;
	
	SFolder* list;
	uLong listSize;
};

#endif