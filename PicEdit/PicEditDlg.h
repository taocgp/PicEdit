// PicEditDlg.h : ͷ�ļ�

#pragma once
// CPicEditDlg �Ի���
class CPicEditDlg : public CDialogEx
{
// ����
public:
	CPicEditDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PICEDIT_DIALOG };

//���ο����ݽṹ
	struct rect{
	int ID;
	int left,top;
	int width,height;
	int r,g,b;
	};

//��������
	CList<rect> rects;
//�����豸������
	CDC mCdc;
	CBitmap mCbitmap;

//ͼƬ�ؼ���ָ��
	CWnd   *pWnd;
//ͼƬ�豸������
	CDC* pdc;
	CBitmap bitmap;
//ͼƬ����
	CRect picRect;
//ȫ��λ�á����α���
	POSITION p;
	rect  arect;

//��������	
	CPen pen;
	CBrush brush;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
//ͼƬ�ؼ�����
	void picPaint();
//ͨ����Ż�������еľ��ο򣬽��������ȫ�ֱ���p��arect��
	void GetRectByID(int ID);
// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
};
