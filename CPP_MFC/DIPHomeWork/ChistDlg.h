#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#pragma once


// ChistDlg �Ի���

class ChistDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChistDlg)

public:
	ChistDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ChistDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_HIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
};
