// NewGameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Chess.h"
#include "SetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetDlg dialog


CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hSetIcon=::AfxGetApp()->LoadIcon(IDI_SET);
	m_bitmapOk.LoadBitmap(IDB_OK);
	m_bitmapCancel.LoadBitmap(IDB_CANCEL);

	m_strTip="搜索引擎,双击可以快捷“确定”";

	m_nSelectedEngine=0;
	m_nSelectedPly=3;	
	m_nUserChessColor=REDCHESS;
	m_nChessSort=CS_PCCHESS;
	m_iDepthSort=DS_DEFAULTSET;
}


void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetDlg)
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_LIST_ENGINE, m_listSearchEngine);
	DDX_Control(pDX, IDC_PLY, m_SetPly);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialog)
	//{{AFX_MSG_MAP(CSetDlg)
	ON_BN_CLICKED(IDC_RADIOBLACKCHESS, OnRadioblackchess)
	ON_BN_CLICKED(IDC_RADIOREDCHESS, OnRadioredchess)
	ON_LBN_DBLCLK(IDC_LIST_ENGINE, OnDblclkListengine)
	ON_BN_CLICKED(IDC_RADIOPC, OnRadiopc)
	ON_BN_CLICKED(IDC_RADIOCC, OnRadiocc)
	ON_BN_CLICKED(IDC_RADIOPP, OnRadiopp)
	ON_BN_CLICKED(IDC_RADIOHASH, OnRadiohash)
	ON_LBN_SELCHANGE(IDC_LIST_ENGINE, OnSelchangeListengine)
	ON_BN_CLICKED(IDC_RADIO_DEFAULTSET, OnRadioDefaultset)
	ON_BN_CLICKED(IDC_RADIO_USERDEFINE, OnRadioUserdefine)
	ON_BN_DOUBLECLICKED(IDC_RADIOPC, OnDoubleclickedRadiopc)
	ON_BN_DOUBLECLICKED(IDC_RADIOCC, OnDoubleclickedRadiocc)
	ON_BN_DOUBLECLICKED(IDC_RADIOPP, OnDoubleclickedRadiopp)
	ON_BN_DOUBLECLICKED(IDC_RADIOHASH, OnDoubleclickedRadiohash)
	ON_BN_DOUBLECLICKED(IDC_RADIOREDCHESS, OnDoubleclickedRadioredchess)
	ON_BN_DOUBLECLICKED(IDC_RADIOBLACKCHESS, OnDoubleclickedRadioblackchess)
	ON_BN_DOUBLECLICKED(IDC_RADIO_DEFAULTSET, OnDoubleclickedRadioDefaultset)
	ON_BN_DOUBLECLICKED(IDC_RADIO_USERDEFINE, OnDoubleclickedRadioUserdefine)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetDlg message handlers

void CSetDlg::OnOK() 
{
	// TODO: Add extra validation here	
	m_nSelectedEngine=m_listSearchEngine.GetCurSel();//保存用户选择的搜索引擎号码	
	m_nSelectedPly=m_SetPly.GetPos();                //保存用户选择的搜索深度

	CDialog::OnOK();
}

BOOL CSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetIcon(m_hSetIcon,1);
	m_btnOk.SetBitmap(m_bitmapOk);
	m_btnCancel.SetBitmap(m_bitmapCancel);

	m_tooltip.Create(this);
	m_tooltip.Activate(1);
	m_tooltip.AddTool(GetDlgItem(IDC_LIST_ENGINE),m_strTip);
	m_tooltip.AddTool(GetDlgItem(IDC_EDTDEPTH),"搜索深度不要太大,太大了你要等很久的,3层就行了,4层也还可以,如果是用历史启发的Alpha+Beta搜索引擎,5层都还行.双击可以快捷“确定”");
	m_tooltip.AddTool(GetDlgItem(IDC_RADIOREDCHESS),"你喜欢红棋朝着你呢,还是黑棋啊.双击可以快捷“确定”");
	m_tooltip.AddTool(GetDlgItem(IDC_RADIOBLACKCHESS),"你喜欢黑棋朝着你呢,还是黑棋啊.双击可以快捷“确定”");	
	m_tooltip.AddTool(GetDlgItem(IDC_RADIOPC),"就是你和计算机下咯.,双击可以快捷“确定”");
	m_tooltip.AddTool(GetDlgItem(IDC_RADIOPP),"就是你和另外一个人下咯.,双击可以快捷“确定”");
	m_tooltip.AddTool(GetDlgItem(IDC_RADIOCC),"就是计算机它自己和自己下咯.,双击可以快捷“确定”");
	m_tooltip.AddTool(GetDlgItem(IDC_RADIOHASH),"就是随便谁跟谁下咯.,双击可以快捷“确定”");
	m_tooltip.AddTool(GetDlgItem(IDC_RADIO_DEFAULTSET),"我会根据棋子数目的减少逐渐增加深度,以提高俺的智能.,双击可以快捷“确定”");
	m_tooltip.AddTool(GetDlgItem(IDC_RADIO_USERDEFINE),"你要怎么设置就怎么设置咯,不过不要太大哦,免得我会吃不消的.,双击可以快捷“确定”");

	//添加搜索引擎
	m_listSearchEngine.AddString("Negamax Search Engine");
	m_listSearchEngine.AddString("AlphaBeta Search Engine");	
	m_listSearchEngine.AddString("Fail-Soft Alpha-Beta Search Engine");
	m_listSearchEngine.AddString("Aspiration Search Engine");
	m_listSearchEngine.AddString("PVS Search Engine");
	m_listSearchEngine.AddString("Iterative Deepening Alphabeta Search");
	m_listSearchEngine.AddString("AlphaBeta+TT Search Engine");
	m_listSearchEngine.AddString("Alphabeta+History Heuristic Search Engine");
	m_listSearchEngine.AddString("Mdt(f) Search Engine");
	m_listSearchEngine.AddString("NegaScout+TT+HH Search Engine");

	m_SetPly.SetRange(1,15);						//设定搜索深度范围
	m_listSearchEngine.SetCurSel(m_nSelectedEngine);//默认选择第一个引擎
	m_SetPly.SetPos(m_nSelectedPly);				//默认的搜索深度为3
	if(m_nUserChessColor==REDCHESS)
		((CButton*)GetDlgItem(IDC_RADIOREDCHESS))->SetCheck(TRUE);
	else
		((CButton*)GetDlgItem(IDC_RADIOBLACKCHESS))->SetCheck(TRUE);

	switch(m_nChessSort)
	{
	case 1:
		((CButton*)GetDlgItem(IDC_RADIOPC))->SetCheck(TRUE);
		break;

	case 2:
		((CButton*)GetDlgItem(IDC_RADIOPP))->SetCheck(TRUE);
		break;

	case 3:
		((CButton*)GetDlgItem(IDC_RADIOCC))->SetCheck(TRUE);
		break;

	case 4:
		((CButton*)GetDlgItem(IDC_RADIOHASH))->SetCheck(TRUE);
		break;
	}

	switch(m_iDepthSort)
	{
	case DS_DEFAULTSET:
		((CButton*)GetDlgItem(IDC_RADIO_DEFAULTSET))->SetCheck(TRUE);
		GetDlgItem(IDC_EDTDEPTH)->EnableWindow(0);
		GetDlgItem(IDC_PLY)->EnableWindow(0);
		break;

	case DS_USERDEFINE:
		((CButton*)GetDlgItem(IDC_RADIO_USERDEFINE))->SetCheck(TRUE);
		GetDlgItem(IDC_EDTDEPTH)->EnableWindow(1);
		GetDlgItem(IDC_PLY)->EnableWindow(1);
		break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetDlg::OnRadioblackchess() 
{
	// TODO: Add your control notification handler code here
	m_nUserChessColor=BLACKCHESS;
}

void CSetDlg::OnRadioredchess() 
{
	// TODO: Add your control notification handler code here
	m_nUserChessColor=REDCHESS;
}

void CSetDlg::OnDblclkListengine() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CSetDlg::OnRadiopc() 
{
	// TODO: Add your control notification handler code here
	m_nChessSort=CS_PCCHESS;
}

void CSetDlg::OnRadiocc() 
{
	// TODO: Add your control notification handler code here
	m_nChessSort=CS_CCCHESS;
}

void CSetDlg::OnRadiopp() 
{
	// TODO: Add your control notification handler code here
	m_nChessSort=CS_PPCHESS;
}

void CSetDlg::OnRadiohash() 
{
	// TODO: Add your control notification handler code here
	m_nChessSort=CS_HASHCHESS;
}

BOOL CSetDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_tooltip.RelayEvent(pMsg);

	return CDialog::PreTranslateMessage(pMsg);
}

void CSetDlg::OnSelchangeListengine() 
{
	// TODO: Add your control notification handler code here
	int iNum=m_listSearchEngine.GetCurSel();

	switch(iNum)
	{
	case 0:
		m_strTip="极大极小值法搜索引擎,双击可以快捷“确定”";
		break;

	case 1:
		m_strTip="Alpha-Beta法搜索引擎,双击可以快捷“确定”";
		break;

	case 2:
		m_strTip="Fail-Soft Alpha-Beta法搜索引擎,双击可以快捷“确定”";
		break;

	case 3:
		m_strTip="渴望搜索引擎,双击可以快捷“确定”";
		break;

	case 4:
		m_strTip="极小窗口搜索引擎,双击可以快捷“确定”";
		break;

	case 5:
		m_strTip="迭代深化搜索引擎,双击可以快捷“确定”";
		break;

	case 6:
		m_strTip="使用置换表的Alpha-Beta搜索引擎,双击可以快捷“确定”";
		break;

	case 7:
		m_strTip="使用历史启发的Alpha-Beta搜索引擎,根据我的经验,它的搜索速度最快,双击可以快捷“确定”";
		break;

	case 8:
		m_strTip="MTD(f)搜索引擎,双击可以快捷“确定”";
		break;

	case 9:
		m_strTip="使用历史启发和置换表的Alpha-Beta搜索引擎搜索引擎,双击可以快捷“确定”";
		break;
	}
	m_tooltip.AddTool(GetDlgItem(IDC_LIST_ENGINE),m_strTip);
}

void CSetDlg::OnRadioDefaultset() 
{
	// TODO: Add your control notification handler code here
	m_iDepthSort=DS_DEFAULTSET;
	GetDlgItem(IDC_EDTDEPTH)->EnableWindow(0);
	GetDlgItem(IDC_PLY)->EnableWindow(0);
}

void CSetDlg::OnRadioUserdefine() 
{
	// TODO: Add your control notification handler code here
	m_iDepthSort=DS_USERDEFINE;
	GetDlgItem(IDC_EDTDEPTH)->EnableWindow(1);
	GetDlgItem(IDC_PLY)->EnableWindow(1);
}

void CSetDlg::OnDoubleclickedRadiopc() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CSetDlg::OnDoubleclickedRadiocc() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CSetDlg::OnDoubleclickedRadiopp() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CSetDlg::OnDoubleclickedRadiohash() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CSetDlg::OnDoubleclickedRadioredchess() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CSetDlg::OnDoubleclickedRadioblackchess() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CSetDlg::OnDoubleclickedRadioDefaultset() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CSetDlg::OnDoubleclickedRadioUserdefine() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}
