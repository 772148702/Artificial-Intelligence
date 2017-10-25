
// TspMFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TspMFC.h"
#include "TspMFCDlg.h"
#include "afxdialogex.h"
#include <stdio.h>
#include<string>
#include <stdlib.h>
#include <fstream>
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


// CTspMFCDlg 对话框



CTspMFCDlg::CTspMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TSPMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CTspMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Paint1, idc_Paint1);
}

BEGIN_MESSAGE_MAP(CTspMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CTspMFCDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_BUTTON_INPUT, &CTspMFCDlg::OnBnClickedButtonInput)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_INPUTOPT, &CTspMFCDlg::OnBnClickedInputopt)

END_MESSAGE_MAP()


// CTspMFCDlg 消息处理程序

BOOL CTspMFCDlg::OnInitDialog()
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

void CTspMFCDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTspMFCDlg::OnPaint()
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
HCURSOR CTspMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CTspMFCDlg::drawEdit(vector<int> tmp) {

	/*
	CEdit * pEdit = (CEdit *)GetDlgItem(IDC_Paint1);
	CRect rect;

	pEdit->GetClientRect(rect);
	int widht = rect.Width();
	int height = rect.Height();
	CDC *pDC = pEdit->GetDC();
	pDC->Rectangle(rect);
	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
	pDC->MoveTo(0, 0);
	pDC->LineTo(20, 20);
	pDC->LineTo(100, 100);*/
	CEdit * pEdit = (CEdit *)GetDlgItem(IDC_Paint1);
	CRect rect;
	pEdit->GetClientRect(rect);
	int widht = rect.Width();
	int height = rect.Height();
	CDC *pDC = pEdit->GetDC();
	pDC->Rectangle(rect);

	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
	//映射在初始话里面完成。
	pDC->MoveTo(x[tmp[0]], y[tmp[0]]);
	for (int i =1; i < tmp.size(); i++)
	{
		pDC->LineTo(x[tmp[i]], y[tmp[i]]);
		pDC->MoveTo(x[tmp[i]], y[tmp[i]]);
	}

	
	
}

void CTspMFCDlg::drawEditOpt(vector<int> tmp) {
	CEdit * pEdit = (CEdit *)GetDlgItem(IDC_Paint2);
	CRect rect;
	pEdit->GetClientRect(rect);
	int widht = rect.Width();
	int height = rect.Height();
	CDC *pDC = pEdit->GetDC();
	pDC->Rectangle(rect);

	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
	//映射在初始话里面完成。
	pDC->MoveTo(x[tmp[0]], y[tmp[0]]);
	for (int i = 1; i < tmp.size(); i++)
	{
		pDC->LineTo(x[tmp[i]], y[tmp[i]]);
		pDC->MoveTo(x[tmp[i]], y[tmp[i]]);
	}
}
UINT CTspMFCDlg::Thread1(LPVOID  param) {
	CTspMFCDlg * p = (CTspMFCDlg *)param;
	p->lqd.SA();
	return 1;
}

void CTspMFCDlg::OnBnClickedStart()
{
	
	// TODO: 在此添加控件通知处理程序代码
	/*vector<int> v;
	for (int i = 1; i <x.size(); i++)
		v.push_back(i);*/
	lqd.init(x, y);
	start = true;
	SetTimer(1, 100, NULL);
	
	/*HANDLE  hThread1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)lqd.SA(),NULL,0, &dwThreadID[0]);
	HANDLE  hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)drawEdit(lqd.getcur()), NULL, 0, &dwThreadID[1]);*/
	CTspMFCDlg * a=this;
	AfxBeginThread(Thread1,a);

    
}


void CTspMFCDlg::OnBnClickedButtonInput()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	char path[256] = { "C:\\Users\\lzy\\Desktop\\lqd\\eil101.tsp" };
	strFilePath = "C:\\Users\\lzy\\Desktop\\lqd\\eil101.tsp";

	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT_PATH, strFilePath);
		
		wcstombs(path, strFilePath, strFilePath.GetLength());
		path[strFilePath.GetLength()] = '\0';
	}
	
	freopen(path, "r", stdin);
	int cnt = 0;
	x.push_back(0);
	y.push_back(0);
	static string ss;
	for (int i = 1; i <= 6; ++i) getline(cin, ss);
	double maxx = -1, maxy = -1;
	double a, b;
	int index;
	while (cin >> index>> a >> b) {
		maxx = max(a, maxx);
		maxy = max(b, maxy);
		x.push_back(a);
		y.push_back(b);
		cnt++;
	}
	
	CEdit * pEdit = (CEdit *)GetDlgItem(IDC_Paint1);
	CRect rect;
	pEdit->GetClientRect(rect);
	int width = rect.Width();
	int height = rect.Height();
	 
	/*for (int i = 1; i <= n; i++) {
		x[i] = x[i] * (width*1.0 / maxx);
		y[i] = y[i] * (height*1.0 / maxy);
	} */
	
	
	
}


void CTspMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (start) {
		if (nIDEvent == 1) {
			drawEdit(lqd.getcur());
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CTspMFCDlg::OnBnClickedInputopt()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("所有文件(*.*)|*.*||");
	// 构造打开文件对话框   
	CFileDialog fileDlg(TRUE, _T("txt"), NULL, 0, szFilter, this);
	CString strFilePath;

	// 显示打开文件对话框   
	char path[256] = { "C:\\Users\\lzy\\Desktop\\lqd\\eil101.tsp.opt" };
	

	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT_PATH, strFilePath);

		wcstombs(path, strFilePath, strFilePath.GetLength());
		path[strFilePath.GetLength()] = '\0';
	}
	fstream in(path);
	
	static string ss;
	for (int i = 1; i <= 4; ++i) getline(in, ss);
	bt.clear();
	int aaa;
	int n = x.size() - 1;
	while (n--) {
		in >> aaa;
		
		bt.push_back(aaa);
	}
	bt.push_back(bt[0]);
	drawEditOpt(bt);
}


