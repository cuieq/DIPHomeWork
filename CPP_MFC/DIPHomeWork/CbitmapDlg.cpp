// CbitmapDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DIPHomeWork.h"
#include "CbitmapDlg.h"
#include "afxdialogex.h"
#include "opencv2\core\core.hpp"

// CbitmapDlg �Ի���

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


// CbitmapDlg ��Ϣ�������

// ����CImage�������Ϊȫ�ֱ�������洢
CImage image; 

void CbitmapDlg::OnBnClickedButton1()
{
    TCHAR szFilter[] = _T("ͼ���ļ�|*.jpg;*.jpeg;*.gif;*.tiff;*.tif;*.png|�����ļ�(*.*)|*.*||");   
    CFileDialog fileDlg(TRUE, _T("*"), NULL, 0, szFilter, this);   
    CString strFilePath;   
    if (IDOK == fileDlg.DoModal())   
    {   
        strFilePath = fileDlg.GetPathName();     
    }   
	
    //����ͼƬ·������ͼƬ
	image.Load(strFilePath); 
    //�����������
	CRect rect;
    //��ȡͼƬ���,�߶�
	int cx = image.GetWidth();
	int cy = image.GetHeight();

	GetDlgItem(IDC_STATIC_BITPIC)->GetWindowRect(&rect);
    //���ͻ���ѡ�е�Picture�ؼ���ʾ�ľ���������
	ScreenToClient(&rect);
    //�������ƶ���Picture�ؼ���ʾ�ľ�������
	GetDlgItem(IDC_STATIC_BITPIC)->MoveWindow(rect.left, rect.top, cx, cy, TRUE);

    //���pictrue�ؼ����ڵľ��
	CWnd *pWnd=GetDlgItem(IDC_STATIC_BITPIC);

    //���pictrue�ؼ����ڵľ�������
	pWnd->GetClientRect(&rect);

    //���pictrue�ؼ���DC
	CDC *pDC=pWnd->GetDC();
	
    //��ͼƬ����Picture�ؼ���ʾ�ľ�������
	image.Draw(pDC->m_hDC, rect); 
    //�ͷ�picture�ؼ���DC
	ReleaseDC(pDC);

    // ��ʾһЩλͼ������Ϣ
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

// ����
void CbitmapDlg::OnBnClickedButton2()
{
	TCHAR szFilter[] = _T("λͼ�ļ�|*.bmp|�����ļ�(*.*)|*.*||");    
    CFileDialog fileDlg(FALSE, _T("bmp"), _T("bitmapimage.bmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);   
    CString strFilePath;   
    if (IDOK == fileDlg.DoModal())   
    {   
        strFilePath = fileDlg.GetPathName();    
    }   
	image.Save(strFilePath);
}
