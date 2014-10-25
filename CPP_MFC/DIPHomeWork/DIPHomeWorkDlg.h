
// DIPHomeWorkDlg.h : ͷ�ļ�
//

#include "CbinaryDlg.h"
#include "CbitmapDlg.h"
#include "CcmykDlg.h"
#include "CgrayDlg.h"
#include "ChistDlg.h"
#pragma once


// CDIPHomeWorkDlg �Ի���
class CDIPHomeWorkDlg : public CDialogEx
{
// ����
public:
	CbinaryDlg m_binaryDlg;
	CbitmapDlg m_bitmapDlg;
	CcmykDlg m_cmykDlg;
	CgrayDlg m_grayDlg;
	ChistDlg m_histDlg;
	CDIPHomeWorkDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DIPHOMEWORK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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