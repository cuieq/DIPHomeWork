#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#pragma once


// CgrayDlg �Ի���

class CgrayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CgrayDlg)

public:
	CgrayDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CgrayDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_GRAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
