
// DIPHomeWorkDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DIPHomeWork.h"
#include "DIPHomeWorkDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDIPHomeWorkDlg 对话框




CDIPHomeWorkDlg::CDIPHomeWorkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDIPHomeWorkDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDIPHomeWorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_tab);
}

BEGIN_MESSAGE_MAP(CDIPHomeWorkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CDIPHomeWorkDlg::OnTcnSelchangeTab)
END_MESSAGE_MAP()


// CDIPHomeWorkDlg 消息处理程序

BOOL CDIPHomeWorkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

    //这里在主窗口添加标签控件，容纳5个功能窗口
	CRect tabRect;   
  
    m_tab.InsertItem(0, _T("位图转换"));        
    m_tab.InsertItem(1, _T("二值化"));  
	m_tab.InsertItem(2, _T("CMYK转换"));  
	m_tab.InsertItem(3, _T("灰度转换"));  
	m_tab.InsertItem(4, _T("直方图均衡化"));  
	m_bitmapDlg.Create(IDD_DIALOG_BIT, &m_tab);
	m_binaryDlg.Create(IDD_DIALOG_BIN, &m_tab);
	m_cmykDlg.Create(IDD_DIALOG_CMYK, &m_tab);
	m_grayDlg.Create(IDD_DIALOG_GRAY, &m_tab);
	m_histDlg.Create(IDD_DIALOG_HIST, &m_tab);
	m_tab.GetClientRect(&tabRect);    // 获取标签控件客户区Rect   
    // 调整tabRect，使其覆盖范围适合放置标签页   
    tabRect.left += 1;                  
    tabRect.right -= 1;   
    tabRect.top += 25;   
    tabRect.bottom -= 1;   
    // 根据调整好的tabRect放置m_bitmapDlg子对话框，并设置为显示   
    m_bitmapDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);   
    // 根据调整好的tabRect放置m_binaryDlg子对话框，并设置为隐藏   
    m_binaryDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
	m_cmykDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
	m_grayDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
	m_histDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDIPHomeWorkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDIPHomeWorkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDIPHomeWorkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//这个方法实现将cv::Mat类显示到Picture Control控件区域
//因为不是我自己写的，所以没有封装进DIPalgorithms.cpp
//因为互联网上大量的文章都使用了这个方法且没有注明作者，无法找到原作者
void CDIPHomeWorkDlg::ShowMatImgToWnd(CWnd* pWnd, cv::Mat img)
{	
    if(img.empty())  return;  
	static BITMAPINFO *bitMapinfo = NULL;
	static bool First=TRUE;
	if(First)
	{		
		BYTE *bitBuffer	= new BYTE[40+4*256];
		if(bitBuffer == NULL)
		{	
			return;
		}
		First=FALSE;
		memset(bitBuffer, 0, 40+4*256);
		bitMapinfo = (BITMAPINFO *)bitBuffer;
		bitMapinfo->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
		bitMapinfo->bmiHeader.biPlanes			= 1;      // 目标设备的级别，必须为1
		for(int i=0; i<256; i++)
		{	//颜色的取值范围 (0-255)
			bitMapinfo->bmiColors[i].rgbBlue  =bitMapinfo->bmiColors[i].rgbGreen =bitMapinfo->bmiColors[i].rgbRed   =(BYTE) i;
		}	
	}
	
    //如果高度为正的，位图的起始位置在左下角。如果高度为负，起始位置在左上角。
	bitMapinfo->bmiHeader.biHeight		    = -img.rows; 
	bitMapinfo->bmiHeader.biWidth		    = img.cols;
    // 每个像素所需的位数，必须是1(双色), 4(16色)，8(256色)或24(真彩色)之一
	bitMapinfo->bmiHeader.biBitCount		= img.channels() *8; 

    CRect drect;       
    pWnd->GetClientRect(drect); 
	
	CClientDC dc(pWnd);
	HDC hDC =dc.GetSafeHdc();
	SetStretchBltMode(hDC, COLORONCOLOR); 
	//内存中的图像数据拷贝到屏幕上
	StretchDIBits(hDC,
					0,
					0,
					drect.right,		//显示窗口宽度
					drect.bottom,		//显示窗口高度
					0,
					0,
					img.cols,		   //图像宽度
					img.rows,		   //图像高度
					img.data,			
					bitMapinfo,			
					DIB_RGB_COLORS, 
					SRCCOPY
				  );
}

//控制标签页的切换
void CDIPHomeWorkDlg::OnTcnSelchangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	CRect tabRect;    // 标签控件客户区的Rect   
  
    // 获取标签控件客户区Rect，并对其调整，以适合放置标签页   
    m_tab.GetClientRect(&tabRect);   
    tabRect.left += 1;   
    tabRect.right -= 1;   
    tabRect.top += 25;   
    tabRect.bottom -= 1;   
  
    switch (m_tab.GetCurSel())   
    {   
    // 如果标签控件当前选择标签为“位图转换”，则显示m_bitmapDlg对话框，隐藏其余对话框   
    case 0:   
        m_bitmapDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);   
        m_binaryDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
		m_cmykDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
		m_grayDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
		m_histDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
        break;   
    case 1:   
        m_bitmapDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
        m_binaryDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW); 
		m_cmykDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
		m_grayDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
		m_histDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
        break; 
	case 2:
		m_bitmapDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
        m_binaryDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
		m_cmykDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW); 
		m_grayDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
		m_histDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 3:
		m_bitmapDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
        m_binaryDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
		m_cmykDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
		m_grayDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW); 
		m_histDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
	case 4:
		m_bitmapDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);   
        m_binaryDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
		m_cmykDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
		m_grayDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW); 
		m_histDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		break;
    default:   
        break;   
    }   
}


