// PicEditDlg.h : 头文件

#pragma once
// CPicEditDlg 对话框
class CPicEditDlg : public CDialogEx
{
// 构造
public:
	CPicEditDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PICEDIT_DIALOG };

//矩形框数据结构
	struct rect{
	int ID;
	int left,top;
	int width,height;
	int r,g,b;
	};

//矩形链表
	CList<rect> rects;
//缓冲设备上下文
	CDC mCdc;
	CBitmap mCbitmap;

//图片控件的指针
	CWnd   *pWnd;
//图片设备上下文
	CDC* pdc;
	CBitmap bitmap;
//图片区域
	CRect picRect;
//全局位置、矩形变量
	POSITION p;
	rect  arect;

//画笔属性	
	CPen pen;
	CBrush brush;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
//图片控件绘制
	void picPaint();
//通过序号获得链表中的矩形框，结果保存在全局变量p和arect中
	void GetRectByID(int ID);
// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
};
