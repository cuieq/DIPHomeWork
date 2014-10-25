// CcmykDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DIPHomeWork.h"
#include "DIPHomeWorkDlg.h"
#include "CcmykDlg.h"
#include "afxdialogex.h"
#include "tiffio.h"

using namespace Gdiplus;

// CcmykDlg 对话框

IMPLEMENT_DYNAMIC(CcmykDlg, CDialogEx)

CcmykDlg::CcmykDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CcmykDlg::IDD, pParent)
	, m_rgb_r(0)
	, m_rgb_g(0)
	, m_rgb_b(0)
	, m_cmyk_c(0)
	, m_cmyk_m(0)
	, m_cmyk_y(0)
	, m_cmyk_k(0)
{

}

CcmykDlg::~CcmykDlg()
{
}

void CcmykDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_rgb_r);
	DDX_Text(pDX, IDC_EDIT2, m_rgb_g);
	DDX_Text(pDX, IDC_EDIT3, m_rgb_b);
	DDX_Text(pDX, IDC_EDIT4, m_cmyk_c);
	DDX_Text(pDX, IDC_EDIT5, m_cmyk_m);
	DDX_Text(pDX, IDC_EDIT6, m_cmyk_y);
	DDX_Text(pDX, IDC_EDIT7, m_cmyk_k);
}


BEGIN_MESSAGE_MAP(CcmykDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CcmykDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CcmykDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &CcmykDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CcmykDlg 消息处理程序

// 原始图像
cv::Mat image_rgb_cmyk;

// 存储CMYK4个通道
std::vector<cv::Mat> image_channel;

// 打开并显示图像
void CcmykDlg::OnBnClickedButton1()
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
	image_rgb_cmyk=cv::imread(path);
	CDIPHomeWorkDlg::ShowMatImgToWnd(GetDlgItem(IDC_STATIC_CMYK) , image_rgb_cmyk);
}	

// 求最大值
float max(float a, float b)
{
	if (a > b)
		return a;
	else
		return b;
}

// 转换器操作
void CcmykDlg::OnBnClickedButton4()
{
	UpdateData(TRUE);
	float rgb_r = m_rgb_r;
	float rgb_g = m_rgb_g;
	float rgb_b = m_rgb_b;
	rgb_r /= 255.0;
	rgb_g /= 255.0;
	rgb_b /= 255.0;
	m_cmyk_k = 1.0-max(rgb_r, max(rgb_g, rgb_b));
	m_cmyk_c = (1.0 - rgb_r - m_cmyk_k) / (1.0 - m_cmyk_k);
	m_cmyk_m = (1.0 - rgb_g - m_cmyk_k) / (1.0 - m_cmyk_k);
	m_cmyk_y = (1.0 - rgb_b - m_cmyk_k) / (1.0 - m_cmyk_k);
	m_cmyk_c = ((float)((int)((m_cmyk_c + 0.005) * 100))) / 100;
	m_cmyk_m = ((float)((int)((m_cmyk_m + 0.005) * 100))) / 100;
	m_cmyk_y = ((float)((int)((m_cmyk_y + 0.005) * 100))) / 100;
	m_cmyk_k = ((float)((int)((m_cmyk_k + 0.005) * 100))) / 100;
	UpdateData(FALSE);
}


void CcmykDlg::OnBnClickedButton2()
{
	rgb2cmyk(image_rgb_cmyk, image_channel);
	TCHAR szFilter[] = _T("图像文件|*.jpg;*.jpeg;*.gif;*.tiff;*.tif;*.png|所有文件(*.*)|*.*||");
	CFileDialog fileDlg(FALSE, _T("tif"), _T("CMYKimage"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	CString strFilePath;
	if (IDOK == fileDlg.DoModal())
	{
		strFilePath = fileDlg.GetPathName();
	}
	const size_t strsize = (strFilePath.GetLength() + 1) * 2;
	char *path = new char[strsize];
	size_t sz = 0;
	wcstombs_s(&sz, path, strsize, strFilePath, _TRUNCATE);
    // 用libtiff来保存CMYK模式图像
	TIFF *output;
	uint32 width, height;
    // 光栅：存储数据
	char *raster;
	output = TIFFOpen(path, "w");
	width = image_channel[0].cols;
	height = image_channel[0].rows;
	raster = (char*)malloc(sizeof(char)*width*height * 4);
    // 初始化光栅
	memset(raster, 0, sizeof(raster));
    // 设置文件标签
	TIFFSetField(output, TIFFTAG_IMAGEWIDTH, width);
	TIFFSetField(output, TIFFTAG_IMAGELENGTH, height);
	TIFFSetField(output, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
	TIFFSetField(output, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_SEPARATED);
	TIFFSetField(output, TIFFTAG_INKSET, INKSET_CMYK);
	TIFFSetField(output, TIFFTAG_NUMBEROFINKS, 4);
	TIFFSetField(output, TIFFTAG_BITSPERSAMPLE, 8, 8, 8, 8);
	TIFFSetField(output, TIFFTAG_SAMPLESPERPIXEL, 4);
    // 把图像数据写入光栅
	char* line = &raster[0];
	for (int row = 0; row < height; row++){
		for (int col = 0; col < width; col++){
			*line++ = image_channel[0].at<char>(row, col);
			*line++ = image_channel[1].at<char>(row, col);
			*line++ = image_channel[2].at<char>(row, col);
			*line++ = image_channel[3].at<char>(row, col);
		}
	}
	TIFFWriteEncodedStrip(output, 0, raster, width * height * 4);
	TIFFClose(output);
}
