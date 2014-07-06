// PicEditDlg.cpp : ʵ���ļ�

#include "stdafx.h"
#include "PicEdit.h"
#include "PicEditDlg.h"
#include "afxdialogex.h"
#define PICHEIGHT 420	//ͼƬ���߶�
#define PICWIDTH 420	//ͼƬ�����

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPicEditDlg �Ի���
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

// CPicEditDlg ��Ϣ�������
BOOL CPicEditDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			//���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		//����Сͼ��
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

//ͼƬ�ؼ�����
void CPicEditDlg::picPaint(){
	pWnd   =   GetDlgItem(IDC_CPIC); // ȡ�ÿؼ���ָ��
	pdc = pWnd->GetWindowDC();//ȡ�ÿؼ��豸
	mCdc.CreateCompatibleDC(NULL);//�����豸��ʼ��
	bitmap.LoadBitmap(IDB_BITMAP1);//����ͼƬ
	mCdc.SelectObject(&bitmap);//ͼƬ���뻺��

	brush.CreateStockObject(NULL_BRUSH);
	mCdc.SelectObject(&brush);//����͸��
	for(p = rects.GetHeadPosition(); NULL != p; rects.GetNext(p)){
		arect = rects.GetAt(p);
		pen.CreatePen(PS_SOLID,1,RGB(arect.r,arect.g,arect.b));//���û�����ɫ
		mCdc.SelectObject(&pen);
		mCdc.Rectangle(arect.left , arect.top , arect.left + arect.width , arect.top + arect.height);//�����豸������
		pen.DeleteObject();
	}
	pdc->BitBlt(0,0,PICWIDTH,PICHEIGHT,&mCdc,0,0,SRCCOPY);//���������ݸ��Ƶ�ͼƬ�ؼ�
	brush.DeleteObject ();
	mCdc.DeleteDC();
	bitmap.DeleteObject();
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void CPicEditDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	picPaint();
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPicEditDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//ͨ����Ż�������еľ��ο򣬽��������ȫ�ֱ���p��arect��
void CPicEditDlg::GetRectByID(int ID){
	p = rects.GetHeadPosition(); 
	while(NULL != p){
		arect = rects.GetAt(p);
		if(ID == arect.ID) 
			return;
		rects.GetNext(p);
	}
}

//��ɾ������ť����
void CPicEditDlg::OnBnClickedButton3()
{
	arect.ID = GetDlgItemInt(IDC_EDIT2);
	GetRectByID(arect.ID);

	if(NULL == p)
		MessageBox(L"�����ڸ���ŵľ��ο�");
	else{//�Ӿ���������ɾ�����ػ�ͼƬ�ؼ�
		rects.RemoveAt(p);
		picPaint();
	}
}

//���ı���ο���ɫ����ť����
void CPicEditDlg::OnBnClickedButton5()
{
	arect.ID = GetDlgItemInt(IDC_EDIT13);
	GetRectByID(arect.ID);
	if(NULL == p)
		MessageBox(L"�����ڸ���ŵľ��ο�");
	else{//��������л��Y��U��Vֵ
		int y = GetDlgItemInt(IDC_EDIT10);
		int u = GetDlgItemInt(IDC_EDIT12);
		int v = GetDlgItemInt(IDC_EDIT11);

		//YUV��ɫ����ת��ΪRGB��ɫ����
		arect.r = 1.164 * (y - 16) + 1.159 * (v - 128);
		arect.g = 1.164 * (y - 16) - 0.38 * (u - 128) - 0.813 * (v - 128);
		arect.b = 1.164 * (y - 16) + 2.018 * (u - 128);
		if(arect.r<0 || arect.r>255 || arect.g<0 || arect.g>255 || arect.b<0 || arect.b>255)
			MessageBox(L"����Y��U��U������");
		else{//�Ӿ���������ɾ����������Ӿ��β��ػ�ͼƬ�ؼ�
			rects.RemoveAt(p);
			rects.AddHead(arect);
			picPaint();
		}
	}
}

//����ӡ���ť����
void CPicEditDlg::OnBnClickedButton4()
{
	int ID = GetDlgItemInt(IDC_EDIT14);
	if(ID > 256 || ID <1)
		MessageBox(L"���ο�����Ҫ����1-256֮�䣡");
	else{
		GetRectByID(ID);
		if(NULL != p)
			MessageBox(L"����ŵľ��ο��Ѵ��ڣ�");
		else
		{
			arect.ID = ID;
			//��������л��R��G��Bֵ
			arect.r = GetDlgItemInt(IDC_EDIT7);
			arect.g = GetDlgItemInt(IDC_EDIT9);
			arect.b = GetDlgItemInt(IDC_EDIT8);

			if(arect.r<0 || arect.r>255 || arect.g<0 || arect.g>255 || arect.b<0 || arect.b>255)
				MessageBox(L"R��G��B��Ҫ����0-255֮�䣡");
			else{//��������л��λ�ô�Сֵ
					arect.left  = GetDlgItemInt(IDC_EDIT3);
					arect.top = GetDlgItemInt(IDC_EDIT4);
					arect.height = GetDlgItemInt(IDC_EDIT6);
					arect.width =  GetDlgItemInt(IDC_EDIT5);

				if(arect.left < 0 || arect.left > PICWIDTH ||
						arect.left + arect.width <= 0 || arect.left + arect.width > PICWIDTH
						|| arect.top < 0 || arect.top > PICHEIGHT ||
						arect.top+arect.height <= 0 || arect.top +  arect.height> PICHEIGHT )
					MessageBox(L"���ο�λ�ô�С����ͼƬ����420*420���ˣ�");
				else{//��������������ػ�ͼƬ�ؼ�
					rects.AddHead(arect);
					picPaint();
				}
			}
		}
	}
}

