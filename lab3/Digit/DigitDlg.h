
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
	algorithm al1;
	algorithm al2;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int cnt1;  //��¼�Ѿ����record����Ŀ
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
