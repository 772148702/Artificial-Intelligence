
// lab1Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "DE.h"
#include "PSO.h"
#include "tchart1.h"
#include "CSeries.h"
#include "CTChart.h"
// Clab1Dlg 对话框
class Clab1Dlg : public CDialogEx
{
// 构造
public:
	Clab1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LAB1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	static UINT Thread1(LPVOID  param);
	static UINT Thread2(LPVOID  param);
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	DE  de;
	PSO pso;
	afx_msg void OnBnClickedStart();
	int id = 3;
	CTchart1 m_chart;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	HANDLE thread1;
	HANDLE thread2;
	int cnt;
	vector<double> vde;
	vector<double> vpso;
	CTchart1 m_chart2;

	afx_msg void OnBnClickedButton2();
};
