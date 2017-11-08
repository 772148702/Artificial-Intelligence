
// DigitDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Digit.h"
#include "DigitDlg.h"
#include "afxdialogex.h"
#include "algorithm.h"
#include <algorithm>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDigitDlg �Ի���



CDigitDlg::CDigitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIGIT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDigitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STATE, listbox);
	DDX_Control(pDX, IDC_LIST_STATE2, listbox2);
	DDX_Control(pDX, IDC_LIST_METHOD, listboxMethod);
	DDX_Control(pDX, IDC_LIST_METHOD2, ListBoxMethod2);
}

BEGIN_MESSAGE_MAP(CDigitDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BNT_START, &CDigitDlg::OnBnClickedBntStart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BNT_RND, &CDigitDlg::OnBnClickedBntRnd)
END_MESSAGE_MAP()


// CDigitDlg ��Ϣ�������

BOOL CDigitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDigitDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDigitDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDigitDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDigitDlg::show(state tmp) {
	
	/*for (int i = 0; i < 9; i++) {
		CString s;
		s.Format(L"%d", tmp.st[i]);
		GetDlgItem(1009 + i)->UpdateData(true);
		GetDlgItem(1009+ i)->SetWindowTextW(s);
		GetDlgItem(1009 + i)->UpdateData(false);
	}*/
}
void CDigitDlg::showState() {
	if (al1.record.size()!=0) {
		CString c;
		c.Format(L"��%d����ǰ�ڵ�\n", cnt1);
		listbox.AddString(c);
		Record re = al1.record.front();
		al1.record.pop();

		c.Format(L"open ������%d���ڵ�\n", re.opensize);
		listbox.AddString(c);
		c.Format(L"close������%d���ڵ�\n", re.closesize);
		listbox.AddString(c);
		c.Format(L"��ǰ�ڵ�Ϊ:\n");
		listbox.AddString(c);
		c.Format(L"��ǰ�ڵ�fnΪ%d,gn:%d,hn:%d\n",re.cur.fn,re.cur.gn,re.cur.hn);
		listbox.AddString(c);
		for (int i = 0; i < 3; i++)
		{
			c.Format(L"%d %d %d", re.cur.st[i * 3], re.cur.st[i * 3 + 1], re.cur.st[i * 3 + 2]);
			listbox.AddString(c);
		}
		cnt1++;
	}
	if (al2.record.size() != 0) {
		CString c;
		c.Format(L"��%d����ǰ�ڵ�\n", cnt2);
		listbox2.AddString(c);
		Record re = al2.record.front();
		al2.record.pop();

		c.Format(L"open ������%d���ڵ�\n", re.opensize);
		listbox2.AddString(c);
		c.Format(L"close������%d���ڵ�\n", re.closesize);
		listbox2.AddString(c);
		c.Format(L"��ǰ�ڵ�Ϊ:\n");
		listbox2.AddString(c);
		c.Format(L"��ǰ�ڵ�fnΪ%d,gn:%d,hn:%d\n", re.cur.fn, re.cur.gn, re.cur.hn);
		listbox2.AddString(c);
		for (int i = 0; i < 3; i++)
		{
			c.Format(L"%d %d %d", re.cur.st[i * 3], re.cur.st[i * 3 + 1], re.cur.st[i * 3 + 2]);
			listbox2.AddString(c);
		}
		cnt2++;
	}
}
void CDigitDlg::OnBnClickedBntStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	listbox.ResetContent();
	vector<int> v;
	for (int i = 0; i < 9; i++) {
		CString s;
		GetDlgItem(1009+i)->GetWindowTextW(s);
		v.push_back(_ttoi(s));
	}
	   cnt1 = 0;
	   cnt2 = 0;
	    al1.init1(v);
	    al2.init2(v);
		CDigitDlg * a = this;
		listbox.AddString(L"��λ��������");
	
	

		AfxBeginThread(Thread1, a);
	
	
		listbox2.AddString(L"������������");
	
		
		AfxBeginThread(Thread2, a);
	
	//SetTimer(1, 0.01,NULL);
	stage = Stage::running;

}
void  CDigitDlg::showMethod() {
	   CString c;
	   int i = 1;
	   c.Format(L"����ʽһ�Ľ��");
	   listboxMethod.AddString(c);
	while (!al1.method.empty()) {
		state tmp = al1.method.top();
		al1.method.pop();
		c.Format(L"��%d��:", i++);
		listboxMethod.AddString(c);
		c.Format(L"fn:%d,dn:%dn,hn:%d", tmp.fn, tmp.gn, tmp.hn);
		listboxMethod.AddString(c);
		for (int j = 0; j < 3; j++) {
			c.Format(L"%d %d %d", tmp.st[j * 3], tmp.st[j * 3 + 1], tmp.st[j * 3 + 2]);
			listboxMethod.AddString(c);
		}
		
	  }
}
void  CDigitDlg::showMethod2() {
	CString c;
	int i = 1;
	c.Format(L"����ʽ���Ľ��");
	ListBoxMethod2.AddString(c);
	while (!al2.method.empty()) {
		state tmp = al2.method.top();
		al2.method.pop();
		c.Format(L"��%d��:", i++);
		ListBoxMethod2.AddString(c);
		c.Format(L"fn:%d,dn:%dn,hn:%d", tmp.fn, tmp.gn, tmp.hn);
		ListBoxMethod2.AddString(c);
		for (int j = 0; j < 3; j++) {
			c.Format(L"%d %d %d", tmp.st[j * 3], tmp.st[j * 3 + 1], tmp.st[j * 3 + 2]);
			ListBoxMethod2.AddString(c);
		}

	}
}

 UINT CDigitDlg::Thread1(LPVOID  param) {
	 
	CDigitDlg * p = (CDigitDlg *)param;
	if (p->al1.run1()) {
		//p->show((p->al1.new_cur));
		p->MessageBox(L"����ʽһ�ҵ��˽�");
		p->showMethod();
		return 1;
	}
	p->MessageBox(L"����ʽһ�޽�");
	return 1;
}
 UINT CDigitDlg::Thread2(LPVOID  param) {
	 CDigitDlg * p = (CDigitDlg *)param;
	 if (p->al2.run2()) {
		// p->show((p->al2.new_cur));
		 p->showMethod2();
		 p->MessageBox(L"����ʽ���ҵ��˽�");
		 
		 return 1;
	 }
	 p->MessageBox(L"����ʽ���޽�");
	 return 1;
 }
 void CDigitDlg::OnTimer(UINT_PTR nIDEvent)
 {
	 // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	 if (nIDEvent == 1) {
		 if (stage == Stage::notrunning) {
			 KillTimer(1);
		 }
		 /*showState();*/
	 }
	 CDialogEx::OnTimer(nIDEvent);
 }


 void CDigitDlg::OnBnClickedBntRnd()
 {
	 // TODO: �ڴ���ӿؼ�֪ͨ����������
	 vector<int> v;
	 srand(time(0));
	 for (int i = 0; i < 9; i++) {
		 v.push_back(i);
	 }
	 for (int i = 0; i < 100; i++) {
		 int k1 = rand() % 9;
		 int k2 = rand() % 9;
		 swap(v[k1], v[k2]);
	 }
	 for (int i = 0; i < 9; i++) {
		 CString s;
		 s.Format(L"%d", v[i]);
		 GetDlgItem(1009 + i)->UpdateData(true);
		 GetDlgItem(1009 + i)->SetWindowTextW(s);
		 GetDlgItem(1009 + i)->UpdateData(false);
	 }
 }
