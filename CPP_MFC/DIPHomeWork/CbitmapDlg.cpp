// CbitmapDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DIPHomeWork.h"
#include "CbitmapDlg.h"
#include "afxdialogex.h"
#include "opencv2\core\core.hpp"

// CbitmapDlg 对话框

IMPLEMENT_DYNAMIC(CbitmapDlg, CDialogEx)

CbitmapDlg::CbitmapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CbitmapDlg::IDD, pParent)
{

	m_width = 0;
	m_dib = _T("");
	m_height = 0;
	m_bpp = 0;
}

CbitmapDlg::~CbitmapDlg()
{
}

void CbitmapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT_ISDIB, m_dib);
	//  DDX_Control(pDX, IDC_EDIT_WIDTH, m_width);
	//  DDX_Control(pDX, IDC_EDIT_HEIGHT, m_height);
	//  DDX_Control(pDX, IDC_EDIT_BPP, m_bpp);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_width);
	DDX_Text(pDX, IDC_EDIT_ISDIB, m_dib);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_height);
	DDX_Text(pDX, IDC_EDIT_BPP, m_bpp);
}


BEGIN_MESSAGE_MAP(CbitmapDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CbitmapDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CbitmapDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CbitmapDlg 消息处理程序

// 创建CImage类对象，设为全局变量方便存储
CImage image; 

void CbitmapDlg::OnBnClickedButton1()
{
    TCHAR szFilter[] = _T("图像文件|*.jpg;*.jpeg;*.gif;*.tiff;*.tif;*.png|所有文件(*.*)|*.*||");   
    CFileDialog fileDlg(TRUE, _T("*"), NULL, 0, szFilter, this);   
    CString strFilePath;   
    if (IDOK == fileDlg.DoModal())   
    {   
        strFilePath = fileDlg.GetPathName();     
    }   
	
    //根据图片路径加载图片
	image.Load(strFilePath); 
    //定义矩形区域
	CRect rect;
    //获取图片宽度,高度
	int cx = image.GetWidth();
	int cy = image.GetHeight();

	GetDlgItem(IDC_STATIC_BITPIC)->GetWindowRect(&rect);
    //将客户区选中到Picture控件表示的矩形区域内
	ScreenToClient(&rect);
    //将窗口移动到Picture控件表示的矩形区域
	GetDlgItem(IDC_STATIC_BITPIC)->MoveWindow(rect.left, rect.top, cx, cy, TRUE);

    //获得pictrue控件窗口的句柄
	CWnd *pWnd=GetDlgItem(IDC_STATIC_BITPIC);

    //获得pictrue控件所在的矩形区域
	pWnd->GetClientRect(&rect);

    //获得pictrue控件的DC
	CDC *pDC=pWnd->GetDC();
	
    //将图片画到Picture控件表示的矩形区域
	image.Draw(pDC->m_hDC, rect); 
    //释放picture控件的DC
	ReleaseDC(pDC);

    // 显示一些位图基本消息
	bool isDIB =image.IsDIBSection();
	CString isDIBtext;
	if(isDIB)
		isDIBtext=CString("True");
	else
		isDIBtext=CString("False");
	m_dib=isDIBtext;
	int image_height=image.GetHeight();
	int image_width=image.GetWidth();
	int image_bpp=image.GetBPP();
	m_width=image_width;m_height=image_height;m_bpp=image_bpp;
	UpdateData(FALSE);
}

// 保存
void CbitmapDlg::OnBnClickedButton2()
{
	TCHAR szFilter[] = _T("位图文件|*.bmp|所有文件(*.*)|*.*||");    
    CFileDialog fileDlg(FALSE, _T("bmp"), _T("bitmapimage.bmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);   
    CString strFilePath;   
    if (IDOK == fileDlg.DoModal())   
    {   
        strFilePath = fileDlg.GetPathName();    
    }   
	image.Save(strFilePath);
}
