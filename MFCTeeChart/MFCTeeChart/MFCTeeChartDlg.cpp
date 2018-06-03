
// MFCTeeChartDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCTeeChart.h"
#include "MFCTeeChartDlg.h"
#include "afxdialogex.h"
#include "TeeChar\aspect.h"
#include "TeeChar\legend.h"

#include "TeeChar\series.h"
#include "TeeChar\point3dseries.h"
#include "TeeChar\pointseries.h"
#include "TeeChar\surfaceseries.h"
#include "global.h"
#include "dmoea.h"
#include "nsga.h"
vector<vector<TSOP>> vde;
vector<vector<one>> vsga;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
void de_work(int id, int demension, vector<vector<TSOP>>& vde);
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCTeeChartDlg 对话框




CMFCTeeChartDlg::CMFCTeeChartDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCTeeChartDlg::IDD, pParent)
//	, m_TChart(0)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTeeChartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TCHART1, m_TChart);
	DDX_Control(pDX, IDC_COMBO_FUN, m_cbxFUN);
	DDX_Control(pDX, IDC_COMBO_DIM, m_cbxDIM);
	DDX_Control(pDX, IDC_COMBO2, algo);
	DDX_Control(pDX, IDC_SPEED, Speed);
	DDX_Control(pDX, IDC_TCHART2, chart2);
}

BEGIN_MESSAGE_MAP(CMFCTeeChartDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DRAW, &CMFCTeeChartDlg::OnClickedDraw)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLE, &CMFCTeeChartDlg::OnBnClickedCle)
	
END_MESSAGE_MAP()


// CMFCTeeChartDlg 消息处理程序

BOOL CMFCTeeChartDlg::OnInitDialog()
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCTeeChartDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCTeeChartDlg::OnPaint()
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
HCURSOR CMFCTeeChartDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




UINT CMFCTeeChartDlg::Thread1(LPVOID  param) {

	CMFCTeeChartDlg * p = (CMFCTeeChartDlg *)param;
	
	if (p->algoid == 0) {
		vde.clear();
		de_work(p->fun_id, p->dim, vde);
	}
	else {
		vsga.clear();
		isNsgaEnd = false;
		work(p->fun_id, p->dim, vsga);
	}

	return 0;
}

UINT CMFCTeeChartDlg::Thread2(LPVOID  param) {


	CMFCTeeChartDlg * p = (CMFCTeeChartDlg *)param;
	p->drawans();
	return 0;
}

//界面接口函数
void CMFCTeeChartDlg::Get_Config() {  //取得函数，维数，代数
	int nIndex = m_cbxFUN.GetCurSel();
	CString strFUN;
	m_cbxFUN.GetLBText(nIndex, strFUN);
	CString strDIM;
	dim = m_cbxDIM.GetCurSel()+2;

	fun_id = nIndex;
	//fun_id = _ttoi(strFUN);  //函数id
	//dim = _ttoi(strDIM);  //维数
	numObjectives = dim;
	//MessageBox(strDIM);
	//MessageBox(strFUN);

	algoid = algo.GetCurSel();
	CString strIT;
	GetDlgItemText(IDC_IT, strIT);
	SetDlgItemText(IDC_IT, strIT);
	iteration = _ttoi(strIT);  //代数
	UpdateData(FALSE);
}

void CMFCTeeChartDlg::drawdmoea(int i) {
	int len = vde[i].size();
	//lineSeries.Clear();
	SeriesIndex.vt = VT_INT;
	m_TChart.Series(0).Clear();
	


		if (numObjectives == 3) {
			m_TChart.GetAspect().SetView3D(TRUE);
			for (int j = 0; j < len; j++) 
				m_TChart.Series(0).GetAsPoint3D().AddXYZ((vde[i][j].indiv.y_obj[0]), (vde[i][j].indiv.y_obj[1]), (vde[i][j].indiv.y_obj[2]), NULL, RGB(255, 255, 255));
			//最优解还没找到数据
			//for (int i = 0; i < 10; i++)
				//m_TChart.Series(1).GetAsPoint3D().AddXYZ(i + 2, i, i, NULL, RGB(255, 255, 255));

			//	CAspect  tmp = chart1.get_Aspect();
			//	tmp.put_View3D(TRUE);

			//	CPoint3DSeries0  tt(chart1.Series(0));
			//chart1.AddSeries((long)tt);
			//	tt.AddXYZ((vde[i][j].indiv.y_obj[0]),( vde[i][j].indiv.y_obj[1]), (vde[i][j].indiv.y_obj[2]), NULL, RGB(255, 255, 0));
			//lineSeries.AddXYZ(vde[i][j].indiv.y_obj[0], vde[i][j].indiv.y_obj[1], vde[i][j].indiv.y_obj[2], NULL, RGB(0, 0, 255));
		}

		else {
			m_TChart.GetAspect().SetView3D(FALSE);
			for (int j = 0; j < len; j++)
			 m_TChart.Series(0).AddXY((vde[i][j].indiv.y_obj[0]), (vde[i][j].indiv.y_obj[1]), NULL ,RGB(255, 255, 255));
			
		}
		//lineSeries.AddXYZ(vde[i][j].indiv.y_obj[0], vde[i][j].indiv.y_obj[1], 0, NULL, RGB(0, 0, 255));
	

}
void de_work(int id, int demension, vector<vector<TSOP>>& vde) {
	strcpy(strFunctionType, "_TCH1");

	int  total_run = 1;         // totoal number of runs
	int  max_gen = 1000;       // maximal number of generations
	int  niche = 20;        // neighborhood size

	char *instances[] = {
		"DTLZ1","DTLZ2","DTLZ3", "DTLZ4"
	}; // names of test instances
	int  nvars[] = {
		10,10,10,10
	};                         // number of variables
	int  nobjs[] = {
		2, 2, 2, 2, 2, 3, 3
	};                                // number of objectives



	strcpy(strTestInstance, instances[id]);
	numVariables = nvars[id];
	

	for (int run = 1; run <= total_run; run++)
	{

		seed = (seed + 111) % 1235;
		rnd_uni_init = -(long)seed;
		TMOEAD  MOEAD;

		if (numObjectives == 3)  MOEAD.run(23, niche, max_gen, run, vde);  //23 -3  popsize 300

		if (numObjectives == 2)  MOEAD.run(99, niche, max_gen, run, vde);  //99 -2  popsize 100

	}


	return;
}
void CMFCTeeChartDlg::OnClickedDraw()
{
	//Get_Config();

	cnt = 0;
	CMFCTeeChartDlg * a = this;
	numObjectives = 3;
	fun_id = 2;
	algoid = 1;
	Get_Config();
	vsga.clear();
	vde.clear();
	thread1 = AfxBeginThread(Thread1, a);
	thread1 = AfxBeginThread(Thread2, a);
	int speed=200;
	isNsgaEnd = false;
	int lo = Speed.GetCurSel();
	if (lo == 1) {
		speed = 400;
	} 
	if (lo == 2) {
		speed = 300;
	}
	if (lo == 3) {
		speed = 200;
	}
	SetTimer(0, speed, NULL);

	
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码


}

void CMFCTeeChartDlg::drawans() {
	chart2.Series(0).Clear();
	chart2.Series(1).Clear();
	if (numObjectives == 3) {
		chart2.GetAspect().SetView3D(TRUE);
		if (fun_id == 0) {
			int nummm = 200;
			double en = 0.5 / nummm;
			for (int t = 0; t <= nummm; t++) {
				for (int k = 0; k <= nummm; k++) {
					
					double x = 0 + en*t;
					double y = 0 + en*k;
					if(0.5 - x - y>=0&& 0.5 - x - y<=0.5)
					chart2.Series(1).GetAsPoint3D().AddXYZ(x, y, 0.5 - x - y,NULL,RGB(255,255,255));
				}
			}
		}
		else {
			int nummm = 200;
			for (int t = 0; t < nummm; t++) {
				for (int k = 0; k < nummm; k++) {
			
					double en = pi/2 / nummm;
					double x = 0 + en*t;
					double y = 0 + en*k;
					chart2.Series(1).GetAsPoint3D().AddXYZ(cos(x)*cos(y), sin(x)*cos(y), sin(y),NULL, RGB(255, 255, 255));
				}
			}

		}
	}
	else {
		chart2.GetAspect().SetView3D(FALSE);

		if (fun_id == 0) {
			for (int t = 0; t < 200; t++) {
				double x = 0 + 0.5 / (200)*t;
				chart2.Series(0).AddXY(x, 0.5 - x, NULL, RGB(255, 255, 255));
			}
		}
		else {
			for (int t = 0; t < 200; t++) {
				double x = 0 + pi/2/ (200)*t;
				chart2.Series(0).AddXY(cos(x), sin(x), NULL, RGB(255, 255, 255));

			}
		}

	}

}
void  CMFCTeeChartDlg::drawnsga(int i) {
	int len = vsga[i].size();
	
	SeriesIndex.vt = VT_INT;
	m_TChart.Series(0).Clear();

	m_TChart.Series(1).Clear();

	if (numObjectives == 3) {
		m_TChart.GetAspect().SetView3D(TRUE);
		for (int j = 0; j < len; j++)
			m_TChart.Series(0).GetAsPoint3D().AddXYZ((vsga[i][j].f[0]), vsga[i][j].f[1], vsga[i][j].f[2], NULL, RGB(255, 255, 255));
		//最优解还没找到数据
		//for (int i = 0; i < 10; i++)
		//m_TChart.Series(1).GetAsPoint3D().AddXYZ(i + 2, i, i, NULL, RGB(255, 255, 255));

		//	CAspect  tmp = chart1.get_Aspect();
		//	tmp.put_View3D(TRUE);

		//	CPoint3DSeries0  tt(chart1.Series(0));
		//chart1.AddSeries((long)tt);
		//	tt.AddXYZ((vde[i][j].indiv.y_obj[0]),( vde[i][j].indiv.y_obj[1]), (vde[i][j].indiv.y_obj[2]), NULL, RGB(255, 255, 0));
		//lineSeries.AddXYZ(vde[i][j].indiv.y_obj[0], vde[i][j].indiv.y_obj[1], vde[i][j].indiv.y_obj[2], NULL, RGB(0, 0, 255));
	}

	else {
		m_TChart.GetAspect().SetView3D(FALSE);
		for (int j = 0; j < len; j++)
			m_TChart.Series(0).AddXY((vsga[i][j].f[0]), vsga[i][j].f[1], NULL, RGB(255, 255, 255));

	}
}



void CMFCTeeChartDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (algoid == 0) {
		if (cnt < vde.size()) {
			drawdmoea(cnt);
			cnt = (cnt + 10);
		}

		else {
			KillTimer(0);
		}
	}
	else {
		if (cnt < vsga.size()) {
			drawnsga(cnt);
			cnt = (cnt + 10);
       }

		else {
		
			KillTimer(0);
		}
	}

	
	CDialogEx::OnTimer(nIDEvent);
	
}


void CMFCTeeChartDlg::OnBnClickedCle()
{
	// TODO: 在此添加控件通知处理程序代码
	m_TChart.Series(0).Clear();
	m_TChart.Series(1).Clear();
	if(algoid==1) {
		isNsgaEnd = true;
	}
	KillTimer(0);
}



