#pragma once
#include "afxcmn.h"
#include "afxdtctl.h"


class CDlgSEMLog_PageB : public CDialog
{
	DECLARE_DYNAMIC(CDlgSEMLog_PageB)

public:
	CDlgSEMLog_PageB(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSEMLog_PageB();

// �Ի�������
	enum { IDD = IDD_DLG_PageB };

protected:
	virtual BOOL OnInitDialog();

protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};
