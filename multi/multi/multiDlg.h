
// multiDlg.h : 头文件
//

#pragma once
#include "CTChart.h"
#include "CSeries.h"
#include "CPoint3DSeries.h"

#include "CAspect.h"
// CmultiDlg 对话框
class CmultiDlg : public CDialogEx
{
// 构造
public:
	CmultiDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MULTI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
public:
	afx_msg void OnBnClickedStart();
	static UINT Thread1(LPVOID  param);
	static UINT Thread2(LPVOID  param);
	HANDLE thread1;
	HANDLE thread2;
	void drawdmoea(int i);
	int cnt;
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CTChart chart1;
};
