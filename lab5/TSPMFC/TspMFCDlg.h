
// TspMFCDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <vector>
#include "lqd2.h"
#include "ga_lqd.h"
#include <iostream>

using namespace std;

// CTspMFCDlg 对话框
class CTspMFCDlg : public CDialogEx
{
// 构造
public:
	CTspMFCDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TSPMFC_DIALOG };
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
	DECLARE_MESSAGE_MAP()
public:
	char curPath[256];
	char optPath[256];
	CEdit idc_Paint1;
	double opt_cost = 0;
	bool start = false;
	lqd2 lqd;
	//ga   gaAl;
	GA * gaV1;
	int m_iTemp;
	double m_dDet = 0.99;
	double max_x;
	double max_y;
	bool input1_done = false;
	bool input2_done = false;
	vector <double> x;
	vector<double> y;
	void  drawEdit(vector<int> tmp, double cur_cost, double temp);
	void  drawEditOpt(vector<int> tmp);
	HANDLE  hThread1;
	vector<int> bt;
	static UINT Thread1(LPVOID  param);
	static UINT Thread2(LPVOID  param);
	void initPath(char* curPath);
	void initOptPath(char * curPath);
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedButtonInput();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedInputopt();
	afx_msg void OnBnClickedStop();
	int m_iInLoop;
	afx_msg void OnBnClickedClear();
	void drawEditGa(vector<int> tmp, double curcost, int generation);
};
