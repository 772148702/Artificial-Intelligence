
// DigitDlg.h : ͷ�ļ�
//

#pragma once
#include "algorithm.h"
#include "afxwin.h"

// CDigitDlg �Ի���
enum Stage {
	running, notrunning
};

class CDigitDlg : public CDialogEx
{
// ����
public:
	CDigitDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIGIT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	algorithm al;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int cnt;  //��¼�Ѿ����record����Ŀ
	Stage stage;
	void showState();
	afx_msg void OnBnClickedBntStart();
	static UINT Thread2(LPVOID  param);
	static UINT Thread1(LPVOID  param);
	void show(state tmp);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListBox listbox;
};
