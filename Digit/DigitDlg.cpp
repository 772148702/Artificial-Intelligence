
// DigitDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Digit.h"
#include "DigitDlg.h"
#include "afxdialogex.h"
#include "algorithm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CDigitDlg 对话框



CDigitDlg::CDigitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIGIT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDigitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STATE, listbox);
}

BEGIN_MESSAGE_MAP(CDigitDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BNT_START, &CDigitDlg::OnBnClickedBntStart)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDigitDlg 消息处理程序

BOOL CDigitDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDigitDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDigitDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDigitDlg::show(state tmp) {
	MessageBox(L"找到了解");
	for (int i = 0; i < 9; i++) {
		CString s;
		s.Format(L"%d", tmp.st[i]);
		GetDlgItem(1009 + i)->UpdateData(true);
		GetDlgItem(1009+ i)->SetWindowTextW(s);
		GetDlgItem(1009 + i)->UpdateData(false);
	}
}
void CDigitDlg::showState() {
	if (al.record.size()!=0) {
		CString c;
		c.Format(L"第%d个当前节点\n", cnt);
		listbox.AddString(c);
		Record re = al.record.front();
		al.record.pop();

		c.Format(L"open 表当中有%d个节点\n", re.opensize);
		listbox.AddString(c);
		c.Format(L"close表当中有%d个节点\n", re.closesize);
		listbox.AddString(c);
		c.Format(L"当前节点为:\n");
		listbox.AddString(c);
		c.Format(L"当前节点fn为%d,gn:%d,hn:%d\n",re.cur.fn,re.cur.gn,re.cur.hn);
		listbox.AddString(c);
		for (int i = 0; i < 3; i++)
		{
			c.Format(L"%d %d %d", re.cur.st[i * 3], re.cur.st[i * 3 + 1], re.cur.st[i * 3 + 2]);
			listbox.AddString(c);
		}
		cnt++;
	}

}
void CDigitDlg::OnBnClickedBntStart()
{
	// TODO: 在此添加控件通知处理程序代码
	vector<int> v;
	for (int i = 0; i < 9; i++) {
		CString s;
		GetDlgItem(1009+i)->GetWindowTextW(s);
		v.push_back(_ttoi(s));
	}
	cnt = 0;
	al.init(v);
	CDigitDlg * a = this;
	AfxBeginThread(Thread1, a);
	SetTimer(1, 10,NULL);
	stage = Stage::running;

}

 UINT CDigitDlg::Thread1(LPVOID  param) {
	CDigitDlg * p = (CDigitDlg *)param;
	if (p->al.run()) {
		p->show((p->al.new_cur));
		return 1;
	}
	p->MessageBox(L"无解");
	return 1;
}

 void CDigitDlg::OnTimer(UINT_PTR nIDEvent)
 {
	 // TODO: 在此添加消息处理程序代码和/或调用默认值
	 if (nIDEvent == 1) {
		 if (stage == Stage::notrunning) {
			 KillTimer(1);
		 }
		 showState();
	 }
	 CDialogEx::OnTimer(nIDEvent);
 }
