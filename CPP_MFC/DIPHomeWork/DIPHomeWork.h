
// DIPHomeWork.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDIPHomeWorkApp:
// �йش����ʵ�֣������ DIPHomeWork.cpp
//

class CDIPHomeWorkApp : public CWinApp
{
public:
	CDIPHomeWorkApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDIPHomeWorkApp theApp;