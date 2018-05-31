
// MFCTeeChartDlg.h : 头文件
//

#pragma once
//#include "tchart1.h"
#include "TeeChar\tchart.h"

// CMFCTeeChartDlg 对话框
class CMFCTeeChartDlg : public CDialogEx
{
// 构造
public:
	CMFCTeeChartDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCTEECHART_DIALOG };

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
	DECLARE_MESSAGE_MAP()
public:
	//CTchart1 m_TChart;
	CTChart m_TChart;
	afx_msg void OnClickedDraw();
	VARIANT SeriesIndex;
	static UINT Thread1(LPVOID  param);
	static UINT Thread2(LPVOID  param);
	HANDLE thread1;
	HANDLE thread2;
	void drawdmoea(int i);
	int cnt;
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
