
// MFCTeeChartDlg.h : ͷ�ļ�
//

#pragma once
//#include "tchart1.h"
#include "TeeChar\tchart.h"
#include "afxwin.h"
#include "tchart1.h"

// CMFCTeeChartDlg �Ի���
class CMFCTeeChartDlg : public CDialogEx
{
// ����
public:
	CMFCTeeChartDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCTEECHART_DIALOG };

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
	//CTchart1 m_TChart;
	CTChart m_TChart;
	afx_msg void OnClickedDraw();
	VARIANT SeriesIndex;
	static UINT Thread1(LPVOID  param);
	static UINT Thread2(LPVOID  param);
	void Get_Config();
	HANDLE thread1;
	HANDLE thread2;
	void drawdmoea(int i);
	void drawnsga(int i);
	int cnt;
	void drawans();
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CComboBox m_cbxFUN;
	CComboBox m_cbxDIM;
	int fun_id ;
	int dim ;
	int iteration = 3000 ;
	int algoid;
	afx_msg void OnBnClickedCle();

	CComboBox algo;
	CComboBox Speed;
};
