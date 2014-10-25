// CbinaryDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DIPHomeWork.h"
#include "DIPHomeWorkDlg.h"
#include "DIPalgorithms.h"
#include "CbinaryDlg.h"
#include "afxdialogex.h"


// CbinaryDlg �Ի���

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


// CbinaryDlg ��Ϣ�������
cv::Mat image;
cv::Mat image_bin;
void CbinaryDlg::OnBnClickedButton2()
{
    // ͨ������ѡ���ļ���λ��
	// ���ù�����   
    TCHAR szFilter[] = _T("ͼ���ļ�|*.jpg;*.jpeg;*.gif;*.tiff;*.tif;*.png|�����ļ�(*.*)|*.*||");   
    CFileDialog fileDlg(TRUE, _T("*"), NULL, 0, szFilter, this);   
    CString strFilePath;   
    if (IDOK == fileDlg.DoModal())   
    {   
        strFilePath = fileDlg.GetPathName();     
    }  
    // ��·��ת��Ϊchar* �ַ���
	const size_t strsize=(strFilePath.GetLength()+1)*2;
	char *path=new char[strsize];
	size_t sz=0;
	wcstombs_s(&sz,path,strsize,strFilePath,_TRUNCATE);   
    // ��ȡͼ��
	image = cv::imread(path); 
    // ���ý�cv::Mat����ʾ��Picture Control�ؼ��ĺ���
	CDIPHomeWorkDlg::ShowMatImgToWnd(GetDlgItem(IDC_STATIC_ORIGIN) , image);
    // ���ƵĴ�������װ��DIPalgorithms.cpp��
	cv::Mat bin_origin=imagebinary(image,127);
	CDIPHomeWorkDlg::ShowMatImgToWnd(GetDlgItem(IDC_STATIC_ORIGIN2) , bin_origin);
    // ���ݳ�ʼ��ֵ(ѡȡ127)����ScrollBar��ʼλ��
	m_slider.SetRange(0, 255);
	m_slider.SetPos(127);
}

void CbinaryDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;
    // ��ȡʵʱ��ֵ
	int threshold=m_slider.GetPos();
    // ��̬���¶�ֵ��ͼ��
	image_bin=imagebinary(image,threshold);
	CDIPHomeWorkDlg::ShowMatImgToWnd(GetDlgItem(IDC_STATIC_ORIGIN2) , image_bin);
}


void CbinaryDlg::OnBnClickedButton1()
{
	TCHAR szFilter[] = _T("ͼ���ļ�|*.jpg;*.jpeg;*.gif;*.tiff;*.tif;*.png|�����ļ�(*.*)|*.*||");    
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
