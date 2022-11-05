
// RussianUIDlg.h : ͷ�ļ�
//

#pragma once
#include "LanguageManagerCtrl.h"
#include "afxwin.h"

// CRussianUIDlg �Ի���
class CRussianUIDlg : public CDialogEx
{
// ����
public:
	CRussianUIDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_RUSSIANUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CLanguageManagerCtrl m_LanguageManagerCtrl;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadioChinese();
	afx_msg void OnBnClickedRadioEnglish();
	afx_msg void OnBnClickedRadioRussian();
};
