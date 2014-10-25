// CbinaryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DIPHomeWork.h"
#include "DIPHomeWorkDlg.h"
#include "DIPalgorithms.h"
#include "CbinaryDlg.h"
#include "afxdialogex.h"


// CbinaryDlg 对话框

IMPLEMENT_DYNAMIC(CbinaryDlg, CDialogEx)

CbinaryDlg::CbinaryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CbinaryDlg::IDD, pParent)
{

}

CbinaryDlg::~CbinaryDlg()
{
}

void CbinaryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
}


BEGIN_MESSAGE_MAP(CbinaryDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CbinaryDlg::OnBnClickedButton2)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CbinaryDlg::OnNMCustomdrawSlider1)
	ON_BN_CLICKED(IDC_BUTTON1, &CbinaryDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CbinaryDlg 消息处理程序
cv::Mat image;
cv::Mat image_bin;
void CbinaryDlg::OnBnClickedButton2()
{
    // 通过窗口选择文件打开位置
	// 设置过滤器   
    TCHAR szFilter[] = _T("图像文件|*.jpg;*.jpeg;*.gif;*.tiff;*.tif;*.png|所有文件(*.*)|*.*||");   
    CFileDialog fileDlg(TRUE, _T("*"), NULL, 0, szFilter, this);   
    CString strFilePath;   
    if (IDOK == fileDlg.DoModal())   
    {   
        strFilePath = fileDlg.GetPathName();     
    }  
    // 把路径转换为char* 字符串
	const size_t strsize=(strFilePath.GetLength()+1)*2;
	char *path=new char[strsize];
	size_t sz=0;
	wcstombs_s(&sz,path,strsize,strFilePath,_TRUNCATE);   
    // 读取图像
	image = cv::imread(path); 
    // 调用将cv::Mat类显示到Picture Control控件的函数
	CDIPHomeWorkDlg::ShowMatImgToWnd(GetDlgItem(IDC_STATIC_ORIGIN) , image);
    // 类似的处理函数封装在DIPalgorithms.cpp中
	cv::Mat bin_origin=imagebinary(image,127);
	CDIPHomeWorkDlg::ShowMatImgToWnd(GetDlgItem(IDC_STATIC_ORIGIN2) , bin_origin);
    // 根据初始阈值(选取127)调整ScrollBar初始位置
	m_slider.SetRange(0, 255);
	m_slider.SetPos(127);
}

void CbinaryDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;
    // 获取实时阈值
	int threshold=m_slider.GetPos();
    // 动态更新二值化图像
	image_bin=imagebinary(image,threshold);
	CDIPHomeWorkDlg::ShowMatImgToWnd(GetDlgItem(IDC_STATIC_ORIGIN2) , image_bin);
}


void CbinaryDlg::OnBnClickedButton1()
{
	TCHAR szFilter[] = _T("图像文件|*.jpg;*.jpeg;*.gif;*.tiff;*.tif;*.png|所有文件(*.*)|*.*||");    
    CFileDialog fileDlg(FALSE, _T("jpeg"), _T("binaryimage"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);   
    CString strFilePath;   
    if (IDOK == fileDlg.DoModal())   
    {   
        strFilePath = fileDlg.GetPathName();    
    }  
	const size_t strsize=(strFilePath.GetLength()+1)*2;
	char *path=new char[strsize];
	size_t sz=0;
	wcstombs_s(&sz,path,strsize,strFilePath,_TRUNCATE);   
	cv::imwrite(path,image_bin);
}
