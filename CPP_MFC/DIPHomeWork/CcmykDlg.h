#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "DIPalgorithms.h"
#pragma once


// CcmykDlg 对话框

class CcmykDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CcmykDlg)

public:
	CcmykDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CcmykDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_CMYK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	float m_rgb_r;
	float m_rgb_g;
	float m_rgb_b;
	float m_cmyk_c;
	float m_cmyk_m;
	float m_cmyk_y;
	float m_cmyk_k;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
};
