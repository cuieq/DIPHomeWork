// CgrayDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "DIPHomeWork.h"
#include "DIPHomeWorkDlg.h"
#include "CgrayDlg.h"
#include "afxdialogex.h"
#include "DIPalgorithms.h"


using namespace cv;

// CgrayDlg �Ի���

IMPLEMENT_DYNAMIC(CgrayDlg, CDialogEx)

CgrayDlg::CgrayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CgrayDlg::IDD, pParent)
{

}

CgrayDlg::~CgrayDlg()
{
}

void CgrayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CgrayDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CgrayDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CgrayDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CgrayDlg ��Ϣ�������
cv::Mat rgb2gray_image;
cv::Mat rgb2gray_image_gray;

void CgrayDlg::OnBnClickedButton1()
{
    TCHAR szFilter[] = _T("ͼ���ļ�|*.jpg;*.jpeg;*.gif;*.tiff;*.tif;*.png|�����ļ�(*.*)|*.*||");   
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
    //��ȡͼ��
	rgb2gray_image = cv::imread(path); 
	CDIPHomeWorkDlg::ShowMatImgToWnd(GetDlgItem(IDC_STATIC_GRAYRGB) , rgb2gray_image);
    //�Ҷ�ת��
	rgb2gray_image_gray=rgb2gray(rgb2gray_image);
	CDIPHomeWorkDlg::ShowMatImgToWnd(GetDlgItem(IDC_STATIC_GRAYGRAY) , rgb2gray_image_gray);
}

void CgrayDlg::OnBnClickedButton2()
{
	TCHAR szFilter[] = _T("ͼ���ļ�|*.jpg;*.jpeg;*.gif;*.tiff;*.tif;*.png|�����ļ�(*.*)|*.*||");    
    CFileDialog fileDlg(FALSE, _T("jpeg"), _T("grayimage"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);   
    CString strFilePath;   
    if (IDOK == fileDlg.DoModal())   
    {   
        strFilePath = fileDlg.GetPathName();    
    }  
	const size_t strsize=(strFilePath.GetLength()+1)*2;
	char *path=new char[strsize];
	size_t sz=0;
	wcstombs_s(&sz,path,strsize,strFilePath,_TRUNCATE);   
    //�洢ͼ��
	cv::imwrite(path,rgb2gray_image_gray);
}
