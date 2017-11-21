// HelpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HelpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHelpDlg dialog


CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHelpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHelpDlg)
	m_strHelp = _T("使用说明：\r\n   本软件是为解决八数码难题而设计的,用户可以在文件中输入八数码难题,然后加载,再点击按钮 自动求解 即可.具体问题输入格式可以通过保存当前问题,然后再打开保存的文件即知.点击按钮 开始游戏 可以产生随机的八数码难题.注意:由于本程序的启发函数不是太好,如果对于较难的问题会产生很多节点,有可能会使空间不足,所以尽量不要出太难的问题难为它.如还有问题，请来信至ahei080210114@hotmail.com，谢谢使用本软件！");
	//}}AFX_DATA_INIT
	//加载位图
	m_bitOk.LoadBitmap(IDB_OK);
	m_hIcon=::AfxGetApp()->LoadIcon(IDI_HELP);
}


void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHelpDlg)
	DDX_Text(pDX, IDC_EDIT_HELP, m_strHelp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialog)
	//{{AFX_MSG_MAP(CHelpDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHelpDlg message handlers

BOOL CHelpDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CButton*)GetDlgItem(IDOK))->SetBitmap(m_bitOk);

	SetIcon(m_hIcon,true);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
