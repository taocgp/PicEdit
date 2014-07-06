// PicEditDlg.cpp : 实现文件

#include "stdafx.h"
#include "PicEdit.h"
#include "PicEditDlg.h"
#include "afxdialogex.h"
#define PICHEIGHT 420	//图片区高度
#define PICWIDTH 420	//图片区宽度

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPicEditDlg 对话框
CPicEditDlg::CPicEditDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPicEditDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPicEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPicEditDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CPicEditDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &CPicEditDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CPicEditDlg::OnBnClickedButton4)
END_MESSAGE_MAP()

// CPicEditDlg 消息处理程序
BOOL CPicEditDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			//设置大图标
	SetIcon(m_hIcon, FALSE);		//设置小图标
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

//图片控件处理
void CPicEditDlg::picPaint(){
	pWnd   =   GetDlgItem(IDC_CPIC); // 取得控件的指针
	pdc = pWnd->GetWindowDC();//取得控件设备
	mCdc.CreateCompatibleDC(NULL);//缓存设备初始化
	bitmap.LoadBitmap(IDB_BITMAP1);//载入图片
	mCdc.SelectObject(&bitmap);//图片载入缓存

	brush.CreateStockObject(NULL_BRUSH);
	mCdc.SelectObject(&brush);//设置透明
	for(p = rects.GetHeadPosition(); NULL != p; rects.GetNext(p)){
		arect = rects.GetAt(p);
		pen.CreatePen(PS_SOLID,1,RGB(arect.r,arect.g,arect.b));//设置画笔颜色
		mCdc.SelectObject(&pen);
		mCdc.Rectangle(arect.left , arect.top , arect.left + arect.width , arect.top + arect.height);//缓存设备画矩形
		pen.DeleteObject();
	}
	pdc->BitBlt(0,0,PICWIDTH,PICHEIGHT,&mCdc,0,0,SRCCOPY);//将缓存内容复制到图片控件
	brush.DeleteObject ();
	mCdc.DeleteDC();
	bitmap.DeleteObject();
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CPicEditDlg::OnPaint()
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
	picPaint();
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPicEditDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//通过序号获得链表中的矩形框，结果保存在全局变量p和arect中
void CPicEditDlg::GetRectByID(int ID){
	p = rects.GetHeadPosition(); 
	while(NULL != p){
		arect = rects.GetAt(p);
		if(ID == arect.ID) 
			return;
		rects.GetNext(p);
	}
}

//“删除”按钮处理
void CPicEditDlg::OnBnClickedButton3()
{
	arect.ID = GetDlgItemInt(IDC_EDIT2);
	GetRectByID(arect.ID);

	if(NULL == p)
		MessageBox(L"不存在该序号的矩形框！");
	else{//从矩形链表中删除并重绘图片控件
		rects.RemoveAt(p);
		picPaint();
	}
}

//“改变矩形框颜色”按钮处理
void CPicEditDlg::OnBnClickedButton5()
{
	arect.ID = GetDlgItemInt(IDC_EDIT13);
	GetRectByID(arect.ID);
	if(NULL == p)
		MessageBox(L"不存在该序号的矩形框！");
	else{//从输入框中获得Y、U、V值
		int y = GetDlgItemInt(IDC_EDIT10);
		int u = GetDlgItemInt(IDC_EDIT12);
		int v = GetDlgItemInt(IDC_EDIT11);

		//YUV颜色参数转化为RGB颜色参数
		arect.r = 1.164 * (y - 16) + 1.159 * (v - 128);
		arect.g = 1.164 * (y - 16) - 0.38 * (u - 128) - 0.813 * (v - 128);
		arect.b = 1.164 * (y - 16) + 2.018 * (u - 128);
		if(arect.r<0 || arect.r>255 || arect.g<0 || arect.g>255 || arect.b<0 || arect.b>255)
			MessageBox(L"请检查Y、U、U参数！");
		else{//从矩形链表中删除、重新添加矩形并重绘图片控件
			rects.RemoveAt(p);
			rects.AddHead(arect);
			picPaint();
		}
	}
}

//“添加”按钮处理
void CPicEditDlg::OnBnClickedButton4()
{
	int ID = GetDlgItemInt(IDC_EDIT14);
	if(ID > 256 || ID <1)
		MessageBox(L"矩形框的序号要介于1-256之间！");
	else{
		GetRectByID(ID);
		if(NULL != p)
			MessageBox(L"该序号的矩形框已存在！");
		else
		{
			arect.ID = ID;
			//从输入框中获得R、G、B值
			arect.r = GetDlgItemInt(IDC_EDIT7);
			arect.g = GetDlgItemInt(IDC_EDIT9);
			arect.b = GetDlgItemInt(IDC_EDIT8);

			if(arect.r<0 || arect.r>255 || arect.g<0 || arect.g>255 || arect.b<0 || arect.b>255)
				MessageBox(L"R、G、B都要介于0-255之间！");
			else{//从输入框中获得位置大小值
					arect.left  = GetDlgItemInt(IDC_EDIT3);
					arect.top = GetDlgItemInt(IDC_EDIT4);
					arect.height = GetDlgItemInt(IDC_EDIT6);
					arect.width =  GetDlgItemInt(IDC_EDIT5);

				if(arect.left < 0 || arect.left > PICWIDTH ||
						arect.left + arect.width <= 0 || arect.left + arect.width > PICWIDTH
						|| arect.top < 0 || arect.top > PICHEIGHT ||
						arect.top+arect.height <= 0 || arect.top +  arect.height> PICHEIGHT )
					MessageBox(L"矩形框位置大小超过图片区（420*420）了！");
				else{//添加至矩形链表并重绘图片控件
					rects.AddHead(arect);
					picPaint();
				}
			}
		}
	}
}

