
// DigitDlg.h : 头文件
//

#pragma once
#include "algorithm.h"
#include "afxwin.h"

// CDigitDlg 对话框
enum Stage {
	running, notrunning
};

class CDigitDlg : public CDialogEx
{
// 构造
public:
	CDigitDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIGIT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	algorithm al1;
	algorithm al2;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int cnt1;  //记录已经输出record的数目
	int cnt2;
	Stage stage;
	void showState();
	afx_msg void OnBnClickedBntStart();
	static UINT Thread2(LPVOID  param);
	static UINT Thread1(LPVOID  param);
	void show(state tmp);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListBox listbox;
	CListBox listbox2;
	afx_msg void OnBnClickedBntRnd();
	void  showMethod();
	void showMethod2();
	CListBox listboxMethod;
	CListBox ListBoxMethod2;
};
