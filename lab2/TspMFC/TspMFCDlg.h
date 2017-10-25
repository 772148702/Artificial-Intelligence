
// TspMFCDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <vector>
#include "lqd2.h"
#include <iostream>

using namespace std;

// CTspMFCDlg �Ի���
class CTspMFCDlg : public CDialogEx
{
// ����
public:
	CTspMFCDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TSPMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit idc_Paint1;

	bool start = false;
	lqd2 lqd;
	
	vector <double> x;
	vector<double> y;
	void  drawEdit(vector<int> tmp);
	void  drawEditOpt(vector<int> tmp);
	HANDLE  hThread1, hTread2;
	DWORD  dwThreadID[3];
	vector<int> bt;
	static UINT Thread1(void *param);
	static UINT Thread2(void *param);
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedButtonInput();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedInputopt();
	
};
