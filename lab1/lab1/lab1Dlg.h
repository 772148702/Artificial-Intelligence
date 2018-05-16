
// lab1Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "DE.h"
#include "PSO.h"
#include "tchart1.h"
#include "CSeries.h"
#include "CTChart.h"
// Clab1Dlg �Ի���
class Clab1Dlg : public CDialogEx
{
// ����
public:
	Clab1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LAB1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	static UINT Thread1(LPVOID  param);
	static UINT Thread2(LPVOID  param);
	// ���ɵ���Ϣӳ�亯��
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
