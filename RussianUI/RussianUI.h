
// RussianUI.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CRussianUIApp:
// �йش����ʵ�֣������ RussianUI.cpp
//

class CRussianUIApp : public CWinApp
{
public:
	CRussianUIApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CRussianUIApp theApp;