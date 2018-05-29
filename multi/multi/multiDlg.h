
// multiDlg.h : ͷ�ļ�
//

#pragma once
#include "CTChart.h"
#include "CSeries.h"
#include "CPoint3DSeries.h"

#include "CAspect.h"
// CmultiDlg �Ի���
class CmultiDlg : public CDialogEx
{
// ����
public:
	CmultiDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MULTI_DIALOG };
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
