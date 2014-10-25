#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#pragma once


// CbinaryDlg �Ի���

class CbinaryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CbinaryDlg)

public:
	CbinaryDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CbinaryDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_BIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
//	afx_msg void OnStnClickedStaticOrigin();
	CStatic m_origin_picture;
//	afx_msg void OnStnClickedStaticOrigin2();
	CStatic m_image_origin;
	CSliderCtrl m_slider;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
};