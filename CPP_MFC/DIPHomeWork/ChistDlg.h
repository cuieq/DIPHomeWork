#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#pragma once


// ChistDlg 对话框

class ChistDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChistDlg)

public:
	ChistDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ChistDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_HIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton3();
};
