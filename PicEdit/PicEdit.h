
// PicEdit.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPicEditApp:
// �йش����ʵ�֣������ PicEdit.cpp
//

class CPicEditApp : public CWinApp
{
public:
	CPicEditApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPicEditApp theApp;