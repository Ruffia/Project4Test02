#pragma once
#include "afxcmn.h"


class CDlgSEMLog_OperationQueryKeyWordSettings : public CDialog
{
	DECLARE_DYNAMIC(CDlgSEMLog_OperationQueryKeyWordSettings)

public:
	CDlgSEMLog_OperationQueryKeyWordSettings(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSEMLog_OperationQueryKeyWordSettings();

// �Ի�������
	enum { IDD = IDD_DLG_SEMLog_OperationKeyWord };

protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};
