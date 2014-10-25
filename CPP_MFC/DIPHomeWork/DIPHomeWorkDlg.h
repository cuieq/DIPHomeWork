
// DIPHomeWorkDlg.h : 头文件
//

#include "CbinaryDlg.h"
#include "CbitmapDlg.h"
#include "CcmykDlg.h"
#include "CgrayDlg.h"
#include "ChistDlg.h"
#pragma once


// CDIPHomeWorkDlg 对话框
class CDIPHomeWorkDlg : public CDialogEx
{
// 构造
public:
	CbinaryDlg m_binaryDlg;
	CbitmapDlg m_bitmapDlg;
	CcmykDlg m_cmykDlg;
	CgrayDlg m_grayDlg;
	ChistDlg m_histDlg;
	CDIPHomeWorkDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DIPHOMEWORK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab;
	afx_msg void OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult);
	static void ShowMatImgToWnd(CWnd* pWnd, cv::Mat img);
};