
// MFCTeeChart.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCTeeChartApp:
// �йش����ʵ�֣������ MFCTeeChart.cpp
//

class CMFCTeeChartApp : public CWinApp
{
public:
	CMFCTeeChartApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCTeeChartApp theApp;