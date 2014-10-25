#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#pragma once


// CgrayDlg 对话框

class CgrayDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CgrayDlg)

public:
	CgrayDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CgrayDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_GRAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
