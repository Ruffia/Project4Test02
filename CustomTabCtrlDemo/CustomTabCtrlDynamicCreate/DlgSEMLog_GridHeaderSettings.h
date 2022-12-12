#pragma once
#include "afxcmn.h"
#include "afxdtctl.h"

class CDlgSEMLog_GridHeaderSettings : public CDialog
{
	DECLARE_DYNAMIC(CDlgSEMLog_GridHeaderSettings)

public:
	CDlgSEMLog_GridHeaderSettings(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSEMLog_GridHeaderSettings();

// 对话框数据
	enum { IDD = IDD_DLG_Grid };

protected:
	virtual BOOL OnInitDialog();

protected:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()
};
