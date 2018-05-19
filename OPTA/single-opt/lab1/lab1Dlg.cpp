
// lab1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "lab1.h"
#include "lab1Dlg.h"
#include "afxdialogex.h"

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


// Clab1Dlg 对话框



Clab1Dlg::Clab1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LAB1_DIALOG, pParent)


	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Clab1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	DDX_Control(pDX, IDC_TCHART4, m_chart);
	DDX_Control(pDX, IDC_TCHART5, m_chart2);
	DDX_Control(pDX, IDC_IT_DE, m_cbxDE);
	DDX_Control(pDX, IDC_IT_PSO, m_cbxPSO);
}

BEGIN_MESSAGE_MAP(Clab1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &Clab1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_START, &Clab1Dlg::OnBnClickedStart)

	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLEAR, &Clab1Dlg::OnBnClickedClear)
END_MESSAGE_MAP()


// Clab1Dlg 消息处理程序

BOOL Clab1Dlg::OnInitDialog()
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
	m_cbxDE.SetCurSel(0);
	m_cbxPSO.SetCurSel(2);
	for (int i = 0; i < 30; i++) {
		opt[i] = (i + 1) * 100;
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Clab1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Clab1Dlg::OnPaint()
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
HCURSOR Clab1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Clab1Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();



}


void Clab1Dlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	GetDlgItemText(IDC_FUN, str);
	id = _ttoi(str);
	if (id == 2) {
		MessageBox(_T("原测试函数文件不包含函数2，所以选择2默认为函数3"));
		id = 3;
	}
	CString opt_str;
	opt_str.Format(_T("%d"), opt[id - 1]),
	SetDlgItemText(IDC_OPT, opt_str);
	int nIndex = m_cbxDE.GetCurSel();
	CString strDE;
	m_cbxDE.GetLBText(nIndex, strDE);
	nIndex = m_cbxPSO.GetCurSel();
	CString strPSO;
	m_cbxPSO.GetLBText(nIndex, strPSO);
	it_de = _ttoi(strDE);
	it_pso = _ttoi(strPSO);
	UpdateData(FALSE);
	if (id > 0 && id <= 30) {
		Clab1Dlg * a = this;
		SetTimer(0, 1000, NULL);
		SetTimer(1, 1000, NULL);
		cnt = 0;
		cnt1 = 0;
		thread1 = AfxBeginThread(Thread1, a);
		thread2 = AfxBeginThread(Thread2, a);
	}
	else {
		MessageBox(_T("请输入函数的编号"));
	}

	
}

UINT Clab1Dlg::Thread1(LPVOID  param) {
	
	Clab1Dlg * p = (Clab1Dlg *)param;

	p->de.run(p->id, p->it_de);
	return 0;
}

UINT Clab1Dlg::Thread2(LPVOID  param) {

	Clab1Dlg * p = (Clab1Dlg *)param;
	p->pso.run(p->id, p->it_pso);
	return 0;
}






void Clab1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (0 == nIDEvent)
	{
		cnt++;
		CSeries lineSeries = (CSeries)m_chart.Series(0);

		lineSeries.Clear();
	
		//lineSeries.
		for (int i = 0; i <cnt*30&&i<de.getResult().size() ; i++)

		{
			if(de.getResult()[i]>0)
			lineSeries.AddXY(i, de.getResult()[i], NULL, NULL);

		}


	}
	else {
		cnt1++;
		CSeries lineSeries = (CSeries)m_chart2.Series(0);

		lineSeries.Clear();

		//lineSeries.
		for (int i = 0; i < cnt1 * 30 && i < pso.getResult().size(); i++)

		{
			if (pso.getResult()[i] > 0)
				lineSeries.AddXY(i, pso.getResult()[i], NULL, NULL);
		}
		
	}
	CDialogEx::OnTimer(nIDEvent);
}






void Clab1Dlg::OnBnClickedClear()
{
	// TODO: 在此添加控件通知处理程序代码
	/*CloseHandle(thread1);
	CloseHandle(thread2);
	KillTimer(0);
	cnt = 0;*/
}
