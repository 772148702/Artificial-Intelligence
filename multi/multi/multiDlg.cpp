
// multiDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "multi.h"
#include "multiDlg.h"
#include "afxdialogex.h"
#include "global.h"
#include "dmoea.h"
#include "nsga.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

vector<vector<TSOP>> vde;
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


// CmultiDlg 对话框



CmultiDlg::CmultiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MULTI_DIALOG, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmultiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TCHART1, chart1);
}

BEGIN_MESSAGE_MAP(CmultiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CmultiDlg::OnBnClickedStart)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CmultiDlg 消息处理程序

BOOL CmultiDlg::OnInitDialog()
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

void CmultiDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CmultiDlg::OnPaint()
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
HCURSOR CmultiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void de_work(int id, int demension, vector<vector<TSOP>>& vde) {
	strcpy(strFunctionType, "_TCH1");

	int  total_run = 1;         // totoal number of runs
	int  max_gen = 250;       // maximal number of generations
	int  niche = 20;        // neighborhood size

	char *instances[] = {
		//"ZDT1","ZDT2","ZDT3","ZDT4","ZDT6","DTLZ1","DTLZ2"
		"DTLZ1","DTLZ2","DTLZ3"
	}; // names of test instances
	int  nvars[] = {
		10,10,10,10
	};                         // number of variables
	int  nobjs[] = {
		2, 2, 2, 2, 2, 3, 3
	};                                // number of objectives



	strcpy(strTestInstance, instances[id]);
	numVariables = nvars[id];
	numObjectives = demension;

	for (int run = 1; run <= total_run; run++)
	{
		vde.clear();
		seed = (seed + 111) % 1235;
		rnd_uni_init = -(long)seed;
		TMOEAD  MOEAD;

		if (numObjectives == 3)  MOEAD.run(23, niche, max_gen, run, vde);  //23 -3  popsize 300

		if (numObjectives == 2)  MOEAD.run(99, niche, max_gen, run, vde);  //99 -2  popsize 100

	}


	return;
}

void CmultiDlg::OnBnClickedStart()
{
	cnt = 0;
	CmultiDlg * a = this;
	SetTimer(0, 1000, NULL);
	thread1 = AfxBeginThread(Thread1, a);
	// TODO: 在此添加控件通知处理程序代码
}

UINT CmultiDlg::Thread1(LPVOID  param) {

	CmultiDlg * p = (CmultiDlg *)param;

	de_work(0, 2, vde);

	return 0;
}

UINT CmultiDlg::Thread2(LPVOID  param) {


	CmultiDlg * p = (CmultiDlg *)param;

	return 0;
}
void CmultiDlg::drawdmoea(int i) {
	

	
	int len = vde[i].size();
	CSeries lineSeries = (CSeries)chart1.Series(0);
	lineSeries.Clear();
	for (int j = 0; j < len; j++) {


		if (numObjectives == 3){

			CPoint3DSeries lineSeries = (CPoint3DSeries)chart1.Series(0);
	       }
		//lineSeries.AddXYZ(vde[i][j].indiv.y_obj[0], vde[i][j].indiv.y_obj[1], vde[i][j].indiv.y_obj[2], NULL, RGB(0, 0, 255));
		else {

		
			lineSeries.AddXY(vde[i][j].indiv.y_obj[0], vde[i][j].indiv.y_obj[1], NULL, RGB(0, 0, 255));
		}
		//lineSeries.AddXYZ(vde[i][j].indiv.y_obj[0], vde[i][j].indiv.y_obj[1], 0, NULL, RGB(0, 0, 255));
	}

}

void CmultiDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	if (cnt < vde.size()) {
		drawdmoea(cnt);
	}
	else {
		KillTimer(1);
	}
	cnt = (cnt + 1);
	CDialogEx::OnTimer(nIDEvent);
}
