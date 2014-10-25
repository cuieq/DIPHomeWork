// ChistDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DIPHomeWork.h"
#include "DIPHomeWorkDlg.h"
#include "DIPalgorithms.h"
#include "ChistDlg.h"
#include "afxdialogex.h"



// ChistDlg 对话框

IMPLEMENT_DYNAMIC(ChistDlg, CDialogEx)

ChistDlg::ChistDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ChistDlg::IDD, pParent)
{

}

ChistDlg::~ChistDlg()
{
}

void ChistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChistDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ChistDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ChistDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &ChistDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON3, &ChistDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// ChistDlg 消息处理程序
// 原始图像
cv::Mat image_hist_origin;
// 均衡化后图像
cv::Mat image_hist_equalized;
// 原始图像可视化直方图
cv::Mat image_hist_image_origin;
// 均衡化后可视化直方图
cv::Mat image_hist_image_equalized;

void ChistDlg::OnBnClickedButton1()
{
    TCHAR szFilter[] = _T("图像文件|*.jpg;*.jpeg;*.gif;*.tiff;*.tif;*.png|所有文件(*.*)|*.*||");   
    CFileDialog fileDlg(TRUE, _T("*"), NULL, 0, szFilter, this);   
    CString strFilePath;   
    if (IDOK == fileDlg.DoModal())   
    {   
        strFilePath = fileDlg.GetPathName();     
    }  
	const size_t strsize=(strFilePath.GetLength()+1)*2;
	char *path=new char[strsize];
	size_t sz=0;
	wcstombs_s(&sz,path,strsize,strFilePath,_TRUNCATE);  
	image_hist_origin = cv::imread(path); 
	CDIPHomeWorkDlg::ShowMatImgToWnd(GetDlgItem(IDC_STATIC_HIST_ORI) , image_hist_origin);
    //绘制并显示原始直方图
	image_hist_image_origin=histvisual(image_hist_origin);
	CDIPHomeWorkDlg::ShowMatImgToWnd(GetDlgItem(IDC_STATIC_HISTIMG_ORI) , image_hist_image_origin);
    //直方图均衡化
	image_hist_equalized=histequalize(image_hist_origin);
	CDIPHomeWorkDlg::ShowMatImgToWnd(GetDlgItem(IDC_STATIC_HIST_OUT) , image_hist_equalized);
    //绘制并显示均衡化后直方图
	image_hist_image_equalized=histvisual(image_hist_equalized);
	CDIPHomeWorkDlg::ShowMatImgToWnd(GetDlgItem(IDC_STATIC_HISTIMG_OUT) , image_hist_image_equalized);

}

//保存图像原始直方图
void ChistDlg::OnBnClickedButton2()
{
	TCHAR szFilter[] = _T("图像文件|*.jpg;*.jpeg;*.gif;*.tiff;*.tif;*.png|所有文件(*.*)|*.*||");    
    CFileDialog fileDlg(FALSE, _T("jpeg"), _T("originhist"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);   
    CString strFilePath;   
    if (IDOK == fileDlg.DoModal())   
    {   
        strFilePath = fileDlg.GetPathName();    
    }  
	const size_t strsize=(strFilePath.GetLength()+1)*2;
	char *path=new char[strsize];
	size_t sz=0;
	wcstombs_s(&sz,path,strsize,strFilePath,_TRUNCATE);   
	cv::imwrite(path,image_hist_image_origin);
}

//保存均衡化后直方图
void ChistDlg::OnBnClickedButton5()
{
	TCHAR szFilter[] = _T("图像文件|*.jpg;*.jpeg;*.gif;*.tiff;*.tif;*.png|所有文件(*.*)|*.*||");    
    CFileDialog fileDlg(FALSE, _T("jpeg"), _T("equalizedhist"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);   
    CString strFilePath;   
    if (IDOK == fileDlg.DoModal())   
    {   
        strFilePath = fileDlg.GetPathName();    
    }  
	const size_t strsize=(strFilePath.GetLength()+1)*2;
	char *path=new char[strsize];
	size_t sz=0;
	wcstombs_s(&sz,path,strsize,strFilePath,_TRUNCATE);   
	cv::imwrite(path,image_hist_image_equalized);
}

//保存均衡化后图像
void ChistDlg::OnBnClickedButton3()
{
	TCHAR szFilter[] = _T("图像文件|*.jpg;*.jpeg;*.gif;*.tiff;*.tif;*.png|所有文件(*.*)|*.*||");    
    CFileDialog fileDlg(FALSE, _T("jpeg"), _T("equalized"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);   
    CString strFilePath;   
    if (IDOK == fileDlg.DoModal())   
    {   
        strFilePath = fileDlg.GetPathName();    
    }  
	const size_t strsize=(strFilePath.GetLength()+1)*2;
	char *path=new char[strsize];
	size_t sz=0;
	wcstombs_s(&sz,path,strsize,strFilePath,_TRUNCATE);   
	cv::imwrite(path,image_hist_equalized);
}
