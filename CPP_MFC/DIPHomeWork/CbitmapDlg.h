#pragma once
#include "afxwin.h"


// CbitmapDlg �Ի���

class CbitmapDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CbitmapDlg)

public:
	CbitmapDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CbitmapDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_BIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
//	CEdit m_dib;
//	CEdit m_width;
//	CEdit m_height;
//	CEdit m_bpp;
	int m_width;
	CString m_dib;
	int m_height;
	int m_bpp;
};
