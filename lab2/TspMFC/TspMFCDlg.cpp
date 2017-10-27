
// TspMFCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TspMFC.h"
#include "TspMFCDlg.h"
#include "afxdialogex.h"
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
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
	, m_dDet(0.98)
	, m_iInLoop(1000)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CTspMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Paint1, idc_Paint1);
	DDX_Text(pDX, IDC_Para_Det, m_dDet);
	DDV_MinMaxDouble(pDX, m_dDet, 0.8, 0.9999);
	DDX_Text(pDX, IDC_Para_InLoop, m_iInLoop);
	DDV_MinMaxInt(pDX, m_iInLoop, 500, 100000);
}

BEGIN_MESSAGE_MAP(CTspMFCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CTspMFCDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_BUTTON_INPUT, &CTspMFCDlg::OnBnClickedButtonInput)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_INPUTOPT, &CTspMFCDlg::OnBnClickedInputopt)
	ON_BN_CLICKED(IDC_STOP, &CTspMFCDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_CLEAR, &CTspMFCDlg::OnBnClickedClear)
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
m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_APP);

SetIcon(m_hIcon, TRUE);			// 设置大图标
SetIcon(m_hIcon, FALSE);		// 设置小图标

// TODO: 在此添加额外的初始化代码
CString warning = L"注意！不支持中文路径";
SetDlgItemText(IDC_TSP_PATH, warning);
SetDlgItemText(IDC_OPT_PATH, warning);
CheckRadioButton(IDC_SA, IDC_LOCAL, IDC_SA);
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
void CTspMFCDlg::drawEdit(vector<int> tmp, double cur_cost, double temp) {

	CEdit * pEdit = (CEdit *)GetDlgItem(IDC_Paint1);
	CRect rect;
	pEdit->GetClientRect(rect);
	int width = rect.Width();
	int height = rect.Height();
	double stdX_scale = width / max_x;
	double stdY_scale = height / max_y;
	CDC *pDC = pEdit->GetDC();
	pDC->Rectangle(rect);
	CPen pen(PS_SOLID, 2, RGB(0, 255, 0));
	CBrush brush(RGB(0, 0, 0));
	//映射在初始话里面完成。
	pDC->SelectObject(brush);
	for (int i = 0; i < tmp.size(); i++) {
		pDC->Ellipse((int)x[tmp[i]] * stdX_scale - 4, (int)y[tmp[i]] * stdY_scale - 4, (int)x[tmp[i]] * stdX_scale + 4, (int)y[tmp[i]] * stdY_scale + 4);
	}
	pDC->SelectObject(pen);
	pDC->MoveTo((int)x[tmp[0]] * stdX_scale, (int)y[tmp[0]] * stdY_scale);
	for (int i = 1; i < tmp.size(); i++)
	{
		pDC->LineTo((int)x[tmp[i]] * stdX_scale, (int)y[tmp[i]] * stdY_scale);
		pDC->MoveTo((int)x[tmp[i]] * stdX_scale, (int)y[tmp[i]] * stdY_scale);
	}
	pDC->LineTo((int)x[tmp[0]] * stdX_scale, (int)y[tmp[0]] * stdY_scale);
	ReleaseDC(pDC);
	double rate = (cur_cost - opt_cost) / opt_cost * 100;
	CString str_Rate;
	CString str_Cost;
	str_Cost.Format(_T("%.2lf"), cur_cost);
	str_Rate.Format(_T("%.2lf"), rate);
	str_Rate += "%";
	CString str_Temp;
	str_Temp.Format(_T("%.3lf"), temp);
	SetDlgItemText(IDC_Error_Rate, str_Rate);
	SetDlgItemText(IDC_Cur_Cost, str_Cost);
	SetDlgItemText(IDC_TEM, str_Temp);
	
}

void CTspMFCDlg::drawEditOpt(vector<int> tmp) {
	CEdit * pEdit = (CEdit *)GetDlgItem(IDC_Paint2);
	CRect rect;
	pEdit->GetClientRect(rect);
	int width = rect.Width();
	int height = rect.Height();
	double stdX_scale = width / max_x;
	double stdY_scale = height / max_y;
	CDC *pDC = pEdit->GetDC();
	pDC->Rectangle(rect);
	CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
	CBrush brush(RGB(0, 0, 0));
	//映射在初始话里面完成。
	pDC->SelectObject(brush);
	for (int i = 0; i < tmp.size(); i++) {
		pDC->Ellipse((int)x[tmp[i]] * stdX_scale - 4, (int)y[tmp[i]] * stdY_scale - 4, (int)x[tmp[i]] * stdX_scale + 4, (int)y[tmp[i]] * stdY_scale + 4);
	}
	pDC->SelectObject(pen);
	pDC->MoveTo((int)x[tmp[0]] * stdX_scale, (int)y[tmp[0]] * stdY_scale);
	for (int i = 1; i < tmp.size(); i++)
	{
		pDC->LineTo((int)x[tmp[i]] * stdX_scale, (int)y[tmp[i]] * stdY_scale);
		pDC->MoveTo((int)x[tmp[i]] * stdX_scale, (int)y[tmp[i]] * stdY_scale);
	}
	pDC->LineTo((int)x[tmp[0]] * stdX_scale, (int)y[tmp[0]] * stdY_scale);
	ReleaseDC(pDC);
}

UINT CTspMFCDlg::Thread1(LPVOID  param) {
	CTspMFCDlg * p = (CTspMFCDlg *)param;
	p->lqd.isEnd = false;
	if (((CButton *)(p->GetDlgItem(IDC_SA)))->GetCheck())
		p->lqd.SA();
	else if (((CButton *)(p->GetDlgItem(IDC_LOCAL)))->GetCheck())
		p->lqd.localsearch();
	return 1;
}

void CTspMFCDlg::initPath(char* path) {
	freopen(path, "r", stdin);
	int cnt = 0;
	string ss;
	getline(cin, ss);
	for (int i = 0; i < ss.size(); ++i) {
		char ch = ss[i];
		if (ch > '9' || ch < '0') continue;
		int j = i;
		while (ch >= '0' && ch <= '9') {
			cnt = cnt * 10 + ch - '0';
			j++;
			if (!ss[j]) break;
			ch = ss[j];
		}
		break;
	}
	int id;
	double c_x, c_y;
	for (int i = 1; i <= 5; ++i) getline(cin, ss);
	x.clear();
	y.clear();
	x.push_back(0);
	y.push_back(0);
	for (int i = 0; i < cnt; ++i) {
		cin >> id >> c_x >> c_y;
		max_x = max(c_x, max_x);
		max_y = max(c_y, max_y);
		x.push_back(c_x);
		y.push_back(c_y);
	}
	fclose(stdin);
}
void CTspMFCDlg::initOptPath(char * path) {
	freopen(path, "r", stdin);
	string ss;
	int index = 0;
	getline(cin, ss);
	getline(cin, ss);
	for (int i = 0; i < ss.size() - 6; i++) {
		if (ss.substr(i, 6) == "Length") {
			index = i;
			index += 7;
			break;
		}
	}
	string opt_ss = ss.substr(index, ss.size() - index);
	if (opt_ss[opt_ss.size() - 1] == ')') opt_ss[opt_ss.size() - 1] = '\0';
	stringstream ssm;
	ssm << opt_ss;
	ssm >> opt_cost;
	ssm.clear();
	getline(cin, ss);
	getline(cin, ss);
	for (int i = 0; i < ss.size() - 9; i++) {
		if (ss.substr(i, 9) == "DIMENSION") {
			index = i;
			index += 12;
			break;
		}
	}
	string str_n = ss.substr(index, ss.size() - index);
	int n;
	stringstream ism;
	ism << str_n;
	ism >> n;
	ism.clear();
	getline(cin, ss);

	bt.clear();
	int city;
	while (n--) {
		cin >> city;
		bt.push_back(city);
	}
	bt.push_back(bt[0]);
	fclose(stdin);
}

void CTspMFCDlg::OnBnClickedStart()
{
	
	// TODO: 在此添加控件通知处理程序代码
	if (input1_done && input2_done) {
		initOptPath(optPath);
		initPath(curPath);
		UpdateData(TRUE);
		/*
		CString det_str;
		GetDlgItem(IDC_Para_Det)->GetWindowText(det_str);
		MessageBox(str);*/
		lqd.init(x, y, m_dDet, m_iInLoop);
		/*CString tt;
		tt.Format(_T("%.2lf"), m_dDet);
		MessageBox(tt);*/
		start = true;
		UpdateData(FALSE);
		SetTimer(1, 200, NULL);
		CTspMFCDlg * a = this;
		hThread1 = AfxBeginThread(Thread1, a);
		drawEditOpt(bt);
	}
	else if (input1_done && !input2_done) MessageBox(L"请选择最优路径文件");
	else if (!input1_done && input2_done) MessageBox(L"请选择tsp文件");
	else if (!input1_done && !input2_done) MessageBox(L"请选择tsp和最优路径文件");
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

	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_TSP_PATH, strFilePath);
		
		wcstombs(path, strFilePath, strFilePath.GetLength());
		path[strFilePath.GetLength()] = '\0';
	}
	strcpy(curPath, path);
	input1_done = true;
}


void CTspMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (start && lqd.isEnd == false) {
		if (nIDEvent == 1) {
			if (lqd.isEnd == false) {
				drawEdit(lqd.getcur(), lqd.get_cost(), lqd.getTem());
			}		
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
	char path[256] = { "C:\\Users\\lzy\\Desktop\\lqd\\eil101.opt.tour" };
	

	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetPathName();
		SetDlgItemText(IDC_OPT_PATH, strFilePath);

		wcstombs(path, strFilePath, strFilePath.GetLength());
		path[strFilePath.GetLength()] = '\0';
	}
	strcpy(optPath, path);
	input2_done = true;
}




void CTspMFCDlg::OnBnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
	lqd.isEnd = true;
	MessageBox(L"已停止程序");
}


void CTspMFCDlg::OnBnClickedClear()
{
	// TODO: 在此添加控件通知处理程序代码
	if (lqd.isEnd == false) {
		MessageBox(L"请先停止程序");
	}
	else {
		CEdit * pEdit1 = (CEdit *)GetDlgItem(IDC_Paint1);
		CEdit * pEdit2 = (CEdit *)GetDlgItem(IDC_Paint2);
		pEdit1->Invalidate();
		pEdit2->Invalidate();
	}
}
