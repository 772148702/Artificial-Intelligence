// ChessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Chess.h"
#include "ChessDlg.h"
#include "NegamaxEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define GRILLEWIDTH  39//������ÿ�����ӵĿ��
#define GRILLEHEIGHT 39//������ÿ�����ӵĸ߶�

const BYTE InitChessBoard[10][9]=
{
	{B_CAR,B_HORSE,B_ELEPHANT,B_BISHOP,B_KING,B_BISHOP,B_ELEPHANT,B_HORSE,B_CAR},
	{NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS},
	{NOCHESS,B_CANON,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,B_CANON,NOCHESS},
	{B_PAWN,NOCHESS,B_PAWN,NOCHESS,B_PAWN,NOCHESS,B_PAWN,NOCHESS,B_PAWN},
	{NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS},
	               //����                       ����//
	{NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS},
	{R_PAWN,NOCHESS,R_PAWN,NOCHESS,R_PAWN,NOCHESS,R_PAWN,NOCHESS,R_PAWN},
	{NOCHESS,R_CANON,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,R_CANON,NOCHESS},
	{NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS,NOCHESS},
	{R_CAR,R_HORSE,R_ELEPHANT,R_BISHOP,R_KING,R_BISHOP,R_ELEPHANT,R_HORSE,R_CAR}
};

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

//����˼���̺߳���
DWORD WINAPI ThinkProc(LPVOID pParam)
{
	CChessDlg* pDlg=(CChessDlg*)pParam;

	pDlg->Think();

	return 0;
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CButton	m_btnOk;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBitmap m_bitmapOk;

	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
	m_bitmapOk.LoadBitmap(IDB_OK);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDOK, m_btnOk);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChessDlg dialog

CChessDlg::CChessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChessDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChessDlg)
	m_strOutputInfo = _T(" ��ӭʹ���й�����    ");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hUndoIcon=AfxGetApp()->LoadIcon(IDI_UNDO);
	m_hRedoIcon=AfxGetApp()->LoadIcon(IDI_REDO);
	m_hComputerIcon=AfxGetApp()->LoadIcon(IDI_COMPUTER);
	m_hStopIcon=AfxGetApp()->LoadIcon(IDI_STOP);

	m_iWhoChess=REDCHESS;
	m_Status=Chessing;
	m_bIsGameOver=false;
	m_nUserChessColor=REDCHESS;
	m_pMG=new CMoveGenerator;	
	m_bIsThinking=false;
	m_nWillChessColor=REDCHESS;
	m_bIsBegin=false;
	m_iBout=0;
	m_strWelcome=" ��ӭʹ���й�����      ";

	m_pSE=new CFAlphaBetaEngine;//����������ֵ��������
	m_pMG=new CMoveGenerator;//�����߷�������
	m_pEvel=new CEveluation; //������ֵ����
}

void CChessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChessDlg)
	DDX_Control(pDX, IDC_BTN_STOP, m_btnStop);
	DDX_Control(pDX, IDC_BTNUNDO, m_btnUndo);
	DDX_Control(pDX, IDC_BTNREDO, m_btnRedo);
	DDX_Control(pDX, IDC_BTNCOMPUTER, m_btnComputer);
	DDX_Control(pDX, IDC_LISTCHESSRECORD, m_lstChessRecord);
	DDX_Control(pDX, IDC_PROGRESSTHINK, m_progressThink);
	DDX_Control(pDX, IDC_OUTPUTINFO, m_staticTip);
	DDX_Text(pDX, IDC_OUTPUTINFO, m_strOutputInfo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChessDlg, CDialog)
	//{{AFX_MSG_MAP(CChessDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDM_SETCHESSBOARD, OnSetchessboard)
	ON_COMMAND(IDM_SET, OnSet)
	ON_COMMAND(IDM_ABOUT, OnAbout)
	ON_COMMAND(IDM_OPENFILE, OnOpenfile)
	ON_COMMAND(IDM_SAVEFILE, OnSavefile)
	ON_COMMAND(IDM_SCBOVER, OnScbover)
	ON_COMMAND(IDM_RPAWN, OnRpawn)
	ON_COMMAND(IDM_RCANON, OnRcanon)
	ON_COMMAND(IDM_RCAR, OnRcar)
	ON_COMMAND(IDM_RHORSE, OnRhorse)
	ON_COMMAND(IDM_RELEPHANT, OnRelephant)
	ON_COMMAND(IDM_RBISHOP, OnRbishop)
	ON_COMMAND(IDM_RKING, OnRking)
	ON_COMMAND(IDM_BPAWN, OnBpawn)
	ON_COMMAND(IDM_BCANON, OnBcanon)
	ON_COMMAND(IDM_BCAR, OnBcar)
	ON_COMMAND(IDM_BHORSE, OnBhorse)
	ON_COMMAND(IDM_BELEPHANT, OnBelephant)
	ON_COMMAND(IDM_BBISHOP, OnBbishop)
	ON_COMMAND(IDM_BKING, OnBking)
	ON_COMMAND(IDM_DELETE, OnDelete)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CLOSE()
	ON_COMMAND(IDM_CLEARCB, OnClearcb)
	ON_COMMAND(IDM_NEWGAME, OnNewgame)
	ON_BN_CLICKED(IDC_BTNCOMPUTER, OnBtncomputer)
	ON_BN_CLICKED(IDC_BTNUNDO, OnBtnundo)
	ON_BN_CLICKED(IDC_BTNREDO, OnBtnredo)
	ON_LBN_DBLCLK(IDC_LISTCHESSRECORD, OnDblclkListchessrecord)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	ON_LBN_SELCHANGE(IDC_LISTCHESSRECORD, OnSelchangeListchessrecord)
	ON_COMMAND(IDM_PREVIEW, OnPreview)
	ON_COMMAND(IDM_PREVIEWOVER, OnPreviewover)
	ON_COMMAND(IDM_HELP, OnHelp)
	ON_COMMAND(IDM_INVERSECB, OnInversecb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChessDlg message handlers

BOOL CChessDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_btnComputer.SetIcon(m_hComputerIcon,32,32);
	m_btnStop.SetIcon(m_hStopIcon,32,32);
	m_btnUndo.SetIcon(m_hUndoIcon,32,32);
	m_btnRedo.SetIcon(m_hRedoIcon,32,32);

	//��ɫ����������
	m_progressThink.SetStartColor(RGB(0xFF,0xFF,0x00));//��ɫ
	m_progressThink.SetEndColor(RGB(0x00,0x93,0x00));  //��ɫ
	m_progressThink.SetBkColor(RGB(0xE6,0xE6,0xFA));   //����ɫ
	m_progressThink.SetTextColor(RGB(0,0,255));
	m_progressThink.ShowPercent(1);

	m_tooltip.Create(this);
	m_tooltip.Activate(1);
	m_tooltip.AddTool(GetDlgItem(IDC_LISTCHESSRECORD),"������Ŀ����Ԥ����ǰ����,˫����Ŀ���Կ�ݻ���");

	m_Chessman.Create(IDB_CHESSMAN,36,14,RGB(0,255,0));//������������ͼ�ε�ImgList�����ڻ�������

	//������δ���ȡ����ͼ�εĿ���
	BITMAP BitMap;
	m_BoardBmp.LoadBitmap(IDB_CHESSBOARD);
	m_BoardBmp.GetBitmap(&BitMap); //ȡBitMap ����
	m_nBoardWidth=BitMap.bmWidth;  //���̿��
	m_nBoardHeight=BitMap.bmHeight;//���̸߶�

	m_BoardBmp.DeleteObject();

	memcpy(m_byChessBoard,InitChessBoard,90);//��ʼ������
	memcpy(m_byShowChessBoard,InitChessBoard,90);
	memcpy(m_byBackupChessBoard,InitChessBoard,90);

	m_pSE->SetSearchDepth(3);      //�趨��������Ϊ3
	m_pSE->SetMoveGenerator(m_pMG);//�����������趨�߷�������
	m_pSE->SetEveluator(m_pEvel);  //�����������趨��ֵ����
	m_pSE->SetUserChessColor(m_nUserChessColor);
								   //�趨�û�Ϊ�ڷ���췽
	m_pSE->SetThinkProgress(&m_progressThink);
								   //�趨������

	m_MoveChess.nChessID=NOCHESS;//���ƶ����������

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChessDlg::OnPaint() 
{
	CPaintDC dc(this);
	CDC MemDC;
	int i,j;
	POINT pt;
	CBitmap* pOldBmp;

	MemDC.CreateCompatibleDC(&dc);
	m_BoardBmp.LoadBitmap(IDB_CHESSBOARD);
	pOldBmp=MemDC.SelectObject(&m_BoardBmp);
	
	//���������ϵ�����
	for(i=0;i<10;i++)
		for(j=0;j<9;j++)
		{			
			if(m_byShowChessBoard[i][j]==NOCHESS)
				continue;

			pt.x=j*GRILLEHEIGHT+14;
			pt.y=i*GRILLEWIDTH+15;
			m_Chessman.Draw(&MemDC,m_byShowChessBoard[i][j]-1,pt,ILD_TRANSPARENT);
		}

	//�����û������϶�������
	if(m_MoveChess.nChessID!=NOCHESS)
		m_Chessman.Draw(&MemDC,m_MoveChess.nChessID-1,m_MoveChess.ptMovePoint,ILD_TRANSPARENT);
	dc.BitBlt(0,0,m_nBoardWidth,m_nBoardHeight,&MemDC,0,0,SRCCOPY);
								 //�����Ƶ�����ˢ�µ���Ļ
	MemDC.SelectObject(&pOldBmp);//�ָ��ڴ�Dc��ԭλͼ	
	MemDC.DeleteDC();            //�ͷ��ڴ�	 
	m_BoardBmp.DeleteObject();   //ɾ������λͼ����
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChessDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CChessDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_iChessSort==CS_CCCHESS)
	{
		m_staticTip.SetWindowText(m_strWelcome);
		return;
	}

	if(m_Status==Previewing)
	{
		m_staticTip.SetWindowText("���ڴ���Ԥ��״̬,��Ҫ����,�뵯���Ҽ��˵��� Ԥ�����");

		return;
	}

	if(m_bIsGameOver)
	{
		m_staticTip.SetWindowText("����,������������");

		return;
	}

	if(m_bIsThinking)//����������
		return;

	int x,y;

	//�����껻��������ϵĸ���
	y=(point.y-14)/GRILLEHEIGHT;
	x=(point.x-15)/GRILLEWIDTH;
		
	//�ж�����Ƿ��������ڣ����ҵ������û�����
	if(y>=0 && y<10 && x>=0 && x<9 && (m_nUserChessColor==REDCHESS?IsRed(m_byChessBoard[y][x]):IsBlack(m_byChessBoard[y][x])))
	{
		memcpy(m_byBackupChessBoard,m_byChessBoard,90);//��������
		
		//����ǰ���ӵ���Ϣװ�룬��¼�ƶ����ӵĽṹ��
		m_ptMoveChess.x=x;
		m_ptMoveChess.y=y;
		m_MoveChess.nChessID=m_byChessBoard[y][x];
		
		//��������ԭλ������ȥ��
		m_byChessBoard[y][x]=NOCHESS;
		m_byShowChessBoard[y][x]=NOCHESS;
		
		//�������е�����λ��������ڵ�
		point.x-=18;
		point.y-=18;
		m_MoveChess.ptMovePoint=point;
		//�ػ���Ļ
		InvalidateRect(NULL,FALSE);
		UpdateWindow();
		SetCapture();//��ռ��꽹��
	}
	else
		if(m_Status==Chessing)
			if(y>=0 && y<10 && x>=0 && x<9 && (m_nUserChessColor!=REDCHESS?IsRed(m_byChessBoard[y][x]):IsBlack(m_byChessBoard[y][x])))
				m_staticTip.SetWindowText("������˼�������ҵ����ӣ����㲻Ҫ�Ҷ�");
			else
				m_staticTip.SetWindowText("���֣�����û�����ӣ���Ϲ��ʲô��");

	CDialog::OnLButtonDown(nFlags, point);
}

void CChessDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_Status!=Chessing)
		return;

	if(m_bIsGameOver)
	{
		m_staticTip.SetWindowText("����,������������");
		return;
	}

	if(m_bIsThinking || m_Status!=Chessing)
		return;

	BOOL bTurnSide=FALSE;
	int x,y;
	CString str;

    //�����껻��������ϵĸ��� 
	y=(point.y-14)/GRILLEHEIGHT;
	x=(point.x-15)/GRILLEWIDTH;
	
	//�ж��Ƿ����ƶ����ӣ����Ҹ����ӵ��ƶ���һ���Ϸ��߷�
//	if(m_MoveChess.nChessID && CMoveGenerator::IsValidMove(m_byBackupChessBoard,m_ptMoveChess.x,m_ptMoveChess.y,x,y,m_nUserChessColor))
	if(m_MoveChess.nChessID && m_pMG->IsValidMove(m_byBackupChessBoard,m_ptMoveChess.x,m_ptMoveChess.y,x,y,m_nUserChessColor))
	{
		//---------���û��߷�ѹջ---------
		m_cmBestMove.From.x=m_ptMoveChess.x;
		m_cmBestMove.From.y=m_ptMoveChess.y;
		m_cmBestMove.To.x=x;
		m_cmBestMove.To.y=y;
		m_cmBestMove.nChessID=m_MoveChess.nChessID;
		m_umUndoMove.cmChessMove=m_cmBestMove;
		m_umUndoMove.nChessID=m_byChessBoard[y][x];
		m_stackUndoMove.push(m_umUndoMove);
		//--------------------------------

		m_btnUndo.EnableWindow(1);//������尴ť
		
		if(m_nUserChessColor==REDCHESS)
			m_iBout++;
		this->AddChessRecord(m_ptMoveChess.x+1,m_ptMoveChess.y+1,x+1,y+1,m_nUserChessColor,m_MoveChess.nChessID);
		m_byChessBoard[y][x]=m_MoveChess.nChessID;
		m_byShowChessBoard[y][x]=m_MoveChess.nChessID;
		bTurnSide=TRUE;
	}
	else//����ָ��ƶ�ǰ������״̬
	{
		memcpy(m_byShowChessBoard,m_byBackupChessBoard,90);
		memcpy(m_byChessBoard,m_byBackupChessBoard,90);
	}
    
	m_MoveChess.nChessID=NOCHESS;//���ƶ����������

	//�ػ���Ļ  
	InvalidateRect(NULL,FALSE);
	UpdateWindow();	
	ReleaseCapture();//�ͷ���꽹��

	if(bTurnSide==TRUE)
	{
		m_btnStop.EnableWindow(1);
		m_hHandle=::CreateThread(0,0,ThinkProc,this,0,&m_dwThreadID);
	}
	else
		m_staticTip.SetWindowText(m_strWelcome);

	CDialog::OnLButtonUp(nFlags,point);
}

void CChessDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bIsThinking)
		return;

	if(m_MoveChess.nChessID)
	{
		if(m_Status==Chessing)
		{
			//��ֹ�������ϳ�����
			if(point.x<15)//���
				point.x=15;
			if(point.y<15)//�ϱ�
				point.y=15;
			if(point.x>m_nBoardWidth-15)//�ұ�				
				point.x=m_nBoardWidth-15;
			if(point.y>m_nBoardHeight-15)//�±�				
				point.y=m_nBoardHeight-15;
			
			//����������λ��������ڴ�
			point.x-=18;
			point.y-=18;
			
			m_MoveChess.ptMovePoint=point;//�����ƶ����ӵ�����	
		}
		else
		{
			//����������λ��������ڴ�
			point.x-=18;
			point.y-=18;
			
			m_MoveChess.ptMovePoint=point;//�����ƶ����ӵ�����	

			//�����ϳ�����ʱ��������ɾ��
			if(point.x<15 || point.y<15 || point.x>m_nBoardWidth-15 || point.y>m_nBoardHeight-15)
				m_byChessBoard[m_ptMoveChess.y][m_ptMoveChess.x]=NOCHESS;
		}

		InvalidateRect(NULL,FALSE);//ˢ�´���
		UpdateWindow();//����ִ��ˢ��
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CChessDlg::OnSetchessboard() 
{
	// TODO: Add your command handler code here
	m_strOutputInfo=" �������Ҽ��������������Ӻ�ɾ������";
	UpdateData(false);
	m_Status=SetChessBoarding;
}

void CChessDlg::OnSet() 
{
	/*// TODO: Add your command handler code here
	if(m_bIsThinking || m_SetDlg.DoModal()==IDCANCEL)
		return;

	if(m_pSE)
		delete m_pSE;//�ͷžɵ���������
	
	if(m_nUserChessColor!=m_SetDlg.GetUserChessColor())
		this->InvertChessBoard(m_byChessBoard);
	m_nUserChessColor=m_SetDlg.GetUserChessColor();
	m_iChessSort=m_SetDlg.GetChessSort();
	m_iDepthSort=m_SetDlg.GetDepthSort();

	if(m_iChessSort==CS_PCCHESS || m_iChessSort==CS_PPCHESS)
		m_btnComputer.EnableWindow(0);
	else
		m_btnComputer.EnableWindow(1);

	switch(m_SetDlg.GetSelectedEngine())
	{
	case 0:
		m_pSE=new CNegaMaxEngine;
		break;
		
	case 1:
		m_pSE=new CAlphaBetaEngine;//����alpha-beta��������
		break;
		
	case 2:
		m_pSE=new CFAlphaBetaEngine;
		break;
		
	case 3:
		m_pSE=new CAspirationSearch;
		break;
		
	case 4:
		m_pSE=new CPVS_Engine;
		break;
		
	case 5:
		m_pSE=new CIDAlphabetaEngine;
		break;
		
	case 6:
		m_pSE=new CAlphaBeta_TTEngine;
		break;
		
	case 7:
		m_pSE=new CAlphabeta_HHEngine;
		break;
		
	case 8:
		m_pSE=new CMTD_fEngine;
		break;
		
	default:
		m_pSE=new CNegaMaxEngine;
		break;
	}
	m_pMG=new CMoveGenerator;//�����߷�������
	m_pEvel=new CEveluation; //������ֵ����

	m_pSE->SetSearchDepth(m_SetDlg.GetSelectedPly());
	m_pSE->SetUserChessColor(m_nUserChessColor);
	m_pSE->SetMoveGenerator(m_pMG);//���߷�������������������
	m_pSE->SetEveluator(m_pEvel);  //����ֵ���Ĵ�����������
	m_pSE->SetThinkProgress(&m_progressThink);
								   //�趨������

	m_pEvel->ClearAccessCount();*/
}

void CChessDlg::OnAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlg;

	dlg.DoModal();
}

void CChessDlg::OnOpenfile() 
{
	// TODO: Add your command handler code here
	CFileDialog m_OpenDlg(TRUE,NULL,"",0,"����(*.cm)|*.cm||");
	
	if(m_OpenDlg.DoModal()==IDCANCEL) 
		return;

	CString strCMFile;
	char* pCMFile;
	FILE* fp;
	int i,j;
	int nUserChessColor;

	strCMFile=m_OpenDlg.GetPathName();
	pCMFile=(LPSTR)(LPCTSTR)strCMFile;

	fp=fopen(pCMFile,"r");
	if(fp==NULL)
	{
		MessageBox("���ļ�����","������ʾ",MB_ICONWARNING);
		return;
	}

	if(MessageBox("�Ƿ񸲸ǵ�ǰ���?","��������",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)==IDNO)
		return;

	for(i=0;i<10;i++)
		for(j=0;j<9;j++)
			fscanf(fp,"%3d",&m_byChessBoard[i][j]);

	fclose(fp);

	for(i=7;i<10;i++)
		for(j=3;j<6;j++)
		{
			if(m_byChessBoard[i][j]==B_KING)
			{
				nUserChessColor=BLACKCHESS;
				break;
			}
			if(m_byChessBoard[i][j]==R_KING)
			{
				nUserChessColor=REDCHESS;
				break;
			}
		}
	if(nUserChessColor!=m_nUserChessColor)
		this->InvertChessBoard(m_byChessBoard);

	m_bIsBegin=false;

	//ˢ����Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CChessDlg::OnSavefile() 
{
	// TODO: Add your command handler code here
	CFileDialog m_SaveDlg(false,NULL,"",0,"����(*.cm)|*.cm||");
	
	if(m_SaveDlg.DoModal()==IDCANCEL) 
		return;

	CString strCMFile;
	char* pCMFile;
	FILE* fp;
	int i,j;

	strCMFile=m_SaveDlg.GetPathName();
	pCMFile=(LPSTR)(LPCTSTR)strCMFile;

	fp=fopen(pCMFile,"w");
	if(fp==NULL)
	{
		MessageBox("���ļ�����","������ʾ",MB_ICONWARNING);
		return;
	}

	for(i=0;i<10;i++)
	{
		for(j=0;j<9;j++)
			fprintf(fp,"%-3d",m_byChessBoard[i][j]);
		fprintf(fp,"\n");
	}

	fclose(fp);
}

void CChessDlg::OnScbover() 
{
	// TODO: Add your command handler code here
	m_Status=Chessing;
	m_strOutputInfo=m_strWelcome;
	UpdateData(false);
}

void CChessDlg::OnRpawn() 
{
	// TODO: Add your command handler code here
	int x,y;

    //�����껻��������ϵĸ��� 
	y=(m_MousePoint.y-14)/GRILLEHEIGHT;
	x=(m_MousePoint.x-15)/GRILLEWIDTH;

	if(IsChessOver(R_PAWN))
	{
		m_strOutputInfo="��������";
		UpdateData(false);

		return;
	}

	if(((y==6 || y==5) && (x==0 || x==2 || x==4 || x==6 || x==8)) || y<5)
		m_byChessBoard[y][x]=R_PAWN;
	else
	{
		m_strOutputInfo="�ô����ܷű�";
		UpdateData(false);
	}

	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CChessDlg::OnRcanon() 
{
	// TODO: Add your command handler code here
	int x,y;

    //�����껻��������ϵĸ��� 
	y=(m_MousePoint.y-14)/GRILLEHEIGHT;
	x=(m_MousePoint.x-15)/GRILLEWIDTH;

	if(IsChessOver(R_CANON))
	{
		m_strOutputInfo="��������";
		UpdateData(false);

		return;
	}

	m_byChessBoard[y][x]=R_CANON;

	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CChessDlg::OnRcar() 
{
	// TODO: Add your command handler code here
	int x,y;

    //�����껻��������ϵĸ��� 
	y=(m_MousePoint.y-14)/GRILLEHEIGHT;
	x=(m_MousePoint.x-15)/GRILLEWIDTH;

	if(IsChessOver(R_CAR))
	{
		m_strOutputInfo="��������";
		UpdateData(false);

		return;
	}

	m_byChessBoard[y][x]=R_CAR;

	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CChessDlg::OnRhorse() 
{
	// TODO: Add your command handler code here
	int x,y;

    //�����껻��������ϵĸ��� 
	y=(m_MousePoint.y-14)/GRILLEHEIGHT;
	x=(m_MousePoint.x-15)/GRILLEWIDTH;

	if(IsChessOver(R_HORSE))
	{
		m_strOutputInfo="��������";
		UpdateData(false);

		return;
	}

	m_byChessBoard[y][x]=R_HORSE;

	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CChessDlg::OnRelephant() 
{
	// TODO: Add your command handler code here
	int x,y;

    //�����껻��������ϵĸ��� 
	y=(m_MousePoint.y-14)/GRILLEHEIGHT;
	x=(m_MousePoint.x-15)/GRILLEWIDTH;

	if(IsChessOver(R_ELEPHANT))
	{
		m_strOutputInfo="��������";
		UpdateData(false);

		return;
	}

	if((y==9 && (x==2 || x==6)) || (y==7 && (x==0 || x==8)) || (y==7 && x==4) || (y==5 && (x==2 || x==6)))
		m_byChessBoard[y][x]=R_ELEPHANT;
	else
	{
		m_strOutputInfo="�ô����ܷ���";
		UpdateData(false);
	}

	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CChessDlg::OnRbishop() 
{
	// TODO: Add your command handler code here
	int x,y;

    //�����껻��������ϵĸ��� 
	y=(m_MousePoint.y-14)/GRILLEHEIGHT;
	x=(m_MousePoint.x-15)/GRILLEWIDTH;

	if(IsChessOver(R_BISHOP))
	{
		m_strOutputInfo="ʿ������";
		UpdateData(false);

		return;
	}

	if(y>=7 && y<=9 && x>=3 && x<=5)
		m_byChessBoard[y][x]=R_BISHOP;
	else
	{
		m_strOutputInfo="�ô����ܷ�ʿ";
		UpdateData(false);
	}

	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CChessDlg::OnRking() 
{
	// TODO: Add your command handler code here
	int x,y;

    //�����껻��������ϵĸ��� 
	y=(m_MousePoint.y-14)/GRILLEHEIGHT;
	x=(m_MousePoint.x-15)/GRILLEWIDTH;

	if(IsChessOver(R_KING))
	{
		m_strOutputInfo="˧������";
		UpdateData(false);

		return;
	}

	if(y>=7 && y<=9 && x>=3 && x<=5)
		m_byChessBoard[y][x]=R_KING;
	else
	{
		m_strOutputInfo="�ô����ܷ�˧";
		UpdateData(false);
	}

	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CChessDlg::OnBpawn() 
{
	// TODO: Add your command handler code here
	int x,y;

    //�����껻��������ϵĸ��� 
	y=(m_MousePoint.y-14)/GRILLEHEIGHT;
	x=(m_MousePoint.x-15)/GRILLEWIDTH;

	if(IsChessOver(B_PAWN))
	{
		m_strOutputInfo="��������";
		UpdateData(false);

		return;
	}

	if(((y==3 || y==4) && (x==0 || x==2 || x==4 || x==6 || x==8)) || y>4)
		m_byChessBoard[y][x]=B_PAWN;
	else
	{
		m_strOutputInfo="�ô����ܷ���";
		UpdateData(false);
	}

	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CChessDlg::OnBcanon() 
{
	// TODO: Add your command handler code here
	int x,y;

	if(IsChessOver(B_CANON))
	{
		m_strOutputInfo="��������";
		UpdateData(false);

		return;
	}

    //�����껻��������ϵĸ��� 
	y=(m_MousePoint.y-14)/GRILLEHEIGHT;
	x=(m_MousePoint.x-15)/GRILLEWIDTH;

	m_byChessBoard[y][x]=B_CANON;

	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CChessDlg::OnBcar() 
{
	// TODO: Add your command handler code here
	int x,y;

    //�����껻��������ϵĸ��� 
	y=(m_MousePoint.y-14)/GRILLEHEIGHT;
	x=(m_MousePoint.x-15)/GRILLEWIDTH;

	if(IsChessOver(B_CAR))
	{
		m_strOutputInfo="��������";
		UpdateData(false);

		return;
	}

	m_byChessBoard[y][x]=B_CAR;

	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CChessDlg::OnBhorse() 
{
	// TODO: Add your command handler code here
	int x,y;

    //�����껻��������ϵĸ��� 
	y=(m_MousePoint.y-14)/GRILLEHEIGHT;
	x=(m_MousePoint.x-15)/GRILLEWIDTH;

	if(IsChessOver(B_HORSE))
	{
		m_strOutputInfo="��������";
		UpdateData(false);

		return;
	}

	m_byChessBoard[y][x]=B_HORSE;

	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CChessDlg::OnBelephant() 
{
	// TODO: Add your command handler code here
	int x,y;

    //�����껻��������ϵĸ��� 
	y=(m_MousePoint.y-14)/GRILLEHEIGHT;
	x=(m_MousePoint.x-15)/GRILLEWIDTH;

	if(IsChessOver(B_ELEPHANT))
	{
		m_strOutputInfo="��������";
		UpdateData(false);

		return;
	}

	if((y==0 && (x==2 || x==6)) || (y==2 && (x==0 || x==8)) || (y==2 && x==4) || (y==4 && (x==2 || x==6)))
		m_byChessBoard[y][x]=B_ELEPHANT;
	else
	{
		m_strOutputInfo="�ô����ܷ���";
		UpdateData(false);
	}

	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CChessDlg::OnBbishop() 
{
	// TODO: Add your command handler code here
	int x,y;

    //�����껻��������ϵĸ��� 
	y=(m_MousePoint.y-14)/GRILLEHEIGHT;
	x=(m_MousePoint.x-15)/GRILLEWIDTH;

	if(IsChessOver(B_BISHOP))
	{
		m_strOutputInfo="ʿ������";
		UpdateData(false);

		return;
	}

	if(y>=0 && y<=2 && x>=3 && x<=5)
		m_byChessBoard[y][x]=B_BISHOP;
	else
	{
		m_strOutputInfo="�ô����ܷ�ʿ";
		UpdateData(false);
	}

	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CChessDlg::OnBking() 
{
	// TODO: Add your command handler code here
	int x,y;

    //�����껻��������ϵĸ��� 
	y=(m_MousePoint.y-14)/GRILLEHEIGHT;
	x=(m_MousePoint.x-15)/GRILLEWIDTH;

	if(IsChessOver(B_KING))
	{
		m_strOutputInfo="��������";
		UpdateData(false);

		return;
	}

	if(y>=0 && y<=2 && x>=3 && x<=5)
		m_byChessBoard[y][x]=B_KING;
	else
	{
		m_strOutputInfo="�ô����ܷŽ�";
		UpdateData(false);
	}

	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CChessDlg::OnDelete() 
{
	// TODO: Add your command handler code here
	int x,y;

    //�����껻��������ϵĸ��� 
	y=(m_MousePoint.y-14)/GRILLEHEIGHT;
	x=(m_MousePoint.x-15)/GRILLEWIDTH;

	//�ж�����Ƿ��������ڣ����ҵ���������
	if(m_MousePoint.x>0 && m_MousePoint.y>0 && m_MousePoint.x<m_nBoardWidth && m_MousePoint.y<m_nBoardHeight)
		m_byChessBoard[y][x]=NOCHESS;

	//�ػ���Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

bool CChessDlg::IsChessOver(int nChessSort)
{
	int i,j;
	UINT uiCount=0;

	for(i=0;i<10;i++)
		for(j=0;j<9;j++)
			if(nChessSort==m_byChessBoard[i][j])
				uiCount++;

	if(nChessSort==B_PAWN || nChessSort==R_PAWN)
		if(uiCount<5)
			return false;
		else
			return true;
	else
		if(nChessSort==B_KING || nChessSort==R_KING)
			if(uiCount<1)
				return false;
			else 
				return true;
		else
			if(uiCount<2)
				return false;
			else
				return true;
}

void CChessDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_Status==Chessing)
	{
		CMenu menu;
		menu.LoadMenu(IDR_MENU_CHESSING);
		ClientToScreen(&point);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y,this);

		return;
	}

	int x,y;

	this->m_MousePoint=point;

	//�����껻��������ϵĸ���
	y=(m_MousePoint.y-14)/GRILLEHEIGHT;
	x=(m_MousePoint.x-15)/GRILLEWIDTH;
	
	memcpy(m_byBackupChessBoard,m_byChessBoard,90);//���ݵ�ǰ����

	//�ж�����Ƿ��������ڣ����ҵ���������
	if(point.x>0 && point.y>0 && point.x<m_nBoardWidth && point.y<m_nBoardHeight)
	{
		CMenu menu;
		menu.LoadMenu(IDR_MENU_SETCHESSBOARDING);
		ClientToScreen(&point);
		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,point.x,point.y,this);	
	}

	CDialog::OnRButtonDown(nFlags, point);
}

void CChessDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_Status==Chessing)
	{
		OnSet();
		return;
	}

	this->m_MousePoint=point;
	OnDelete();

	CDialog::OnLButtonDblClk(nFlags, point);
}

int CChessDlg::IsGameOver(BYTE position[][9])
{
	int i,j;
	BOOL RedLive=FALSE,BlackLive=FALSE;

	//���췽�Ź��Ƿ���˧
	for(i=7;i<10;i++)
		for(j=3;j<6;j++)
		{
			if(position[i][j]==B_KING)
				BlackLive=TRUE;
			if(position[i][j]==R_KING)
				RedLive=TRUE;
		}

	//���ڷ��Ź��Ƿ��н�
	for(i=0;i<3;i++)
		for(j=3;j<6;j++)
		{
			if(position[i][j]==B_KING)
				BlackLive=TRUE;
			if(position[i][j]==R_KING)
				RedLive=TRUE;
		}

	if(m_nUserChessColor==REDCHESS)
	{
		if(!RedLive)
			return 1;
		
		if(!BlackLive)
			return -1;
	}
	else
	{
		if(!RedLive)
			return -1;
		
		if(!BlackLive)
			return 1;
	}

	return 0;
}

void CChessDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(MessageBox("��ȷ��Ҫ�˳���?","��������",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)==IDNO)
		return;

	CDialog::OnClose();
}

void CChessDlg::OnClearcb() 
{
	// TODO: Add your command handler code here
	if(MessageBox("��ȷ��Ҫ���������?","��������",MB_ICONQUESTION | MB_DEFBUTTON2 | MB_YESNO)==IDNO)
		return;

	int i,j;

	for(i=0;i<10;i++)
		for(j=0;j<9;j++)
			m_byChessBoard[i][j]=NOCHESS;

	//ˢ����Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CChessDlg::InvertChessBoard(BYTE cb[][9])
{
	int i,j;
	BYTE btTemp;

	for(i=0;i<5;i++)
		for(j=0;j<9;j++)
		{
			btTemp=cb[i][j];
			cb[i][j]=cb[9-i][8-j];
			cb[9-i][8-j]=btTemp;
		}

	//ˢ����Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

//void CChessDlg::OnBtnbegin() 
//{
//	// TODO: Add your control notification handler code here
//	CString sNodeCount;
//	int timecount;
//
//	if(m_nUserChessColor==BLACKCHESS)
//	{
//		m_iBout++;
//		m_bIsThinking=true;
//		m_pSE->SearchAGoodMove(m_byChessBoard);//�õ�������һ��	
//		m_cmBestMove=m_pSE->GetBestMove();   //�õ�����߷�
//		m_umUndoMove=m_pSE->GetUndoMove();
//		m_stackUndoMove.push(m_umUndoMove);  //�������߷�ѹջ
//		this->AddChessRecord(m_cmBestMove.From.x+1,m_cmBestMove.From.y+1,m_cmBestMove.To.x+1,m_cmBestMove.To.y+1,m_nUserChessColor,m_cmBestMove.nChessID);		
//		m_bIsThinking=false;
//
//		sNodeCount.Format("������%d���ڵ�,����ʱ��%.3fs",m_pEvel->GetAccessCount(),(GetTickCount()-timecount)/1000.0);
//		m_staticTip.SetWindowText(sNodeCount);
//
//		::FlashWindow(this->GetSafeHwnd(),TRUE);
//	}
//	else
//		m_staticTip.SetWindowText("���֣�������");
//
//	//�ػ���Ļ  
//	InvalidateRect(NULL,FALSE);
//	UpdateWindow();
//
//	m_bIsBegin=true;
//}

void CChessDlg::AddChessRecord(int nFromX,int nFromY,int nToX,int nToY,int nUserChessColor,int nSourceID)
{
	CString strChess;
	CString str;

	if(nUserChessColor==REDCHESS)//�û�ִ����
		str=this->GetMoveStr(nFromX,nFromY,nToX,nToY,nSourceID);
	else
	{
		InvertChessBoard(m_byChessBoard);
		str=this->GetMoveStr(10-nFromX,11-nFromY,10-nToX,11-nToY,nSourceID);
		InvertChessBoard(m_byChessBoard);
	}
	str.Format("%d--"+str,m_iBout);

	m_lstChessRecord.AddString(str);
	m_lstChessRecord.PostMessage(WM_VSCROLL,SB_BOTTOM,0);
}

CString CChessDlg::ConvertDigit2Chinese(int nNum)
{
	switch(nNum)
	{
	case 1:
		return "һ";
		
	case 2:
		return "��";
		
	case 3:
		return "��";
		
	case 4:
		return "��";
		
	case 5:
		return "��";
		
	case 6:
		return "��";
		
	case 7:
		return "��";
		
	case 8:
		return "��";
		
	case 9:
		return "��";

	default:
		return "";
	}
}

void CChessDlg::OnNewgame() 
{
	// TODO: Add your command handler code here
	if(MessageBox("��ȷ��Ҫ������һ����?","��������",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2)==IDNO)
		return;

	memcpy(m_byChessBoard,InitChessBoard,90);    //��ʼ������
	memcpy(m_byShowChessBoard,InitChessBoard,90);
	memcpy(m_byBackupChessBoard,InitChessBoard,90);
	m_MoveChess.nChessID=NOCHESS;                //����ƶ�����
	m_bIsGameOver=false;

	if(m_nUserChessColor==BLACKCHESS)
		this->InvertChessBoard(m_byChessBoard);

	int nCount=m_lstChessRecord.GetCount();
	for(int i=0;i<nCount;i++)
		m_lstChessRecord.DeleteString(i);

	//ˢ����Ļ
	InvalidateRect(NULL,FALSE);
	UpdateWindow();

	m_bIsBegin=false;

	//���ջ
	while(!m_stackUndoMove.empty())
		m_stackUndoMove.pop();
	while(!m_stackRedoMove.empty())
		m_stackRedoMove.pop();

	m_staticTip.SetWindowText(m_strWelcome);
	m_btnUndo.EnableWindow(0);
	m_btnRedo.EnableWindow(0);
	m_btnStop.EnableWindow(0);
}

void CChessDlg::OnBtncomputer() 
{
	// TODO: Add your control notification handler code here
	m_iWhoChess=m_iWhoChess%2+1;
	m_btnStop.EnableWindow(1);
	m_hHandle=::CreateThread(0,0,ThinkProc,this,0,&m_dwThreadID);
}

void CChessDlg::OnBtnundo() 
{
	// TODO: Add your control notification handler code here
	if(m_stackUndoMove.empty())
		return;

	m_btnRedo.EnableWindow(1);//������尴ť
	m_bIsGameOver=false;

	for(int i=0;i<2;i++)
	{
		m_umUndoMove=m_stackUndoMove.top();
		m_stackRedoMove.push(m_umUndoMove);
		m_pSE->UndoChessMove(m_byChessBoard,&m_umUndoMove.cmChessMove,m_umUndoMove.nChessID);
		memcpy(m_byShowChessBoard,m_byChessBoard,90);
		memcpy(m_byBackupChessBoard,m_byChessBoard,90);
		m_stackUndoMove.pop();
		m_lstChessRecord.DeleteString(m_lstChessRecord.GetCount()-1);
		
		//�ػ���Ļ  
		InvalidateRect(NULL,FALSE);
		UpdateWindow();
	}
	m_iBout--;

	if(m_stackUndoMove.empty())
	{
		m_staticTip.SetWindowText("���ѻ���,����ɻ���");
		m_btnUndo.EnableWindow(0);//������尴ť
	}
}

void CChessDlg::OnBtnredo() 
{
	// TODO: Add your control notification handler code here
	if(m_stackRedoMove.empty())
		return;

	UNDOMOVE umTemp;
	
	m_iBout++;
	m_btnUndo.EnableWindow(1);//������尴ť
	for(int i=0;i<2;i++)
	{
		umTemp=m_stackRedoMove.top();
		m_pSE->RedoChessMove(m_byChessBoard,&umTemp.cmChessMove);
		memcpy(m_byShowChessBoard,m_byChessBoard,90);
		memcpy(m_byBackupChessBoard,m_byChessBoard,90);
		m_stackUndoMove.push(umTemp);
		m_stackRedoMove.pop();
		this->AddChessRecord(umTemp.cmChessMove.From.x+1,umTemp.cmChessMove.From.y+1,umTemp.cmChessMove.To.x+1,umTemp.cmChessMove.To.y+1,m_nUserChessColor,umTemp.cmChessMove.nChessID);

		//�ػ���Ļ  
		InvalidateRect(NULL,FALSE);
		UpdateWindow();
	}

	if(m_stackRedoMove.empty())
	{
		m_staticTip.SetWindowText("���ѻ�ԭ��,����ɻ�ԭ��");
		m_btnRedo.EnableWindow(0);//���ỹԭ��ť
	}

	switch(IsGameOver(m_byChessBoard))
	{
	case -1:
		m_staticTip.SetWindowText("����,���ǿŶ");
		break;

	case 1:
		m_staticTip.SetWindowText("����,�����㲻���ҵĶ��ְ�");
		break;

	default:
		return;
	}
	
	m_bIsGameOver=true;
}

CString CChessDlg::GetMoveStr(int nFromX,int nFromY,int nToX,int nToY,int nSourceID)
{
	CString str;
	bool bIsAgain;
	int i;
	int nCount;
	int nPos[5];
	int j=0;

	switch(nSourceID)
	{
	case B_KING://�ڽ�
		if(nFromY==nToY)
		{
			str.Format("�ڣ���%dƽ%d",nFromX,nToX);
			break;
		}
		
		if(nFromY>nToY)
			str.Format("�ڣ���%d��%d",nFromX,nFromY-nToY);
		else
			str.Format("�ڣ���%d��%d",nFromX,nToY-nFromY);
		
		break;
		
	case B_CAR://�ڳ�
		bIsAgain=false;
		for(i=0;i<10;i++)
			if(m_byChessBoard[i][nFromX-1]==B_CAR && i!=nFromY-1 && i!=nToY-1)
			{
				bIsAgain=true;
				break;
			}
			
			if(nFromY>nToY)
			{
				if(bIsAgain)
				{
					if(i>nFromY-1)
						str.Format("�ڣ��󳵽�%d",nFromY-nToY);
					else
						str.Format("�ڣ�ǰ����%d",nFromY-nToY);
				}
				else
					str.Format("�ڣ���%d��%d",nFromX,nFromY-nToY);
			}
			else
				if(nFromY<nToY)
				{						
					if(bIsAgain)
					{
						if(i>nFromY-1)
							str.Format("�ڣ��󳵽�%d",nToY-nFromY);
						else
							str.Format("�ڣ�ǰ����%d",nToY-nFromY);
					}
					else
						str.Format("�ڣ���%d��%d",nFromX,nToY-nFromY);
				}
				else
				{
					if(bIsAgain)
					{
						if(i>nFromY-1)
							str.Format("�ڣ���ƽ%d",nToX);
						else
							str.Format("�ڣ�ǰ��ƽ%d",nToX);
					}
					else
						str.Format("�ڣ���%dƽ%d",nFromX,nToX);
					
					break;
				}
				
				break;
				
	case B_HORSE://����
		bIsAgain=false;
		for(i=0;i<10;i++)
			if(m_byChessBoard[i][nFromX-1]==B_HORSE && i!=nFromY-1 && i!=nToY-1)
			{
				bIsAgain=true;
				break;
			}
			
			if(bIsAgain)
			{
				if(i>nFromY-1)
				{
					if(nFromY>nToY)
						str.Format("�ڣ�������%d",nToX);
					else
						str.Format("�ڣ������%d",nToX);
				}
				else
				{
					if(nFromY>nToY)
						str.Format("�ڣ�ǰ����%d",nToX);
					else
						str.Format("�ڣ�ǰ���%d",nToX);
				}
			}
			else
			{
				if(nFromY>nToY)
					str.Format("�ڣ���%d��%d",nFromX,nToX);
				else
					str.Format("�ڣ���%d��%d",nFromX,nToX);
			}
			
			break;
			
	case B_CANON://����	
		bIsAgain=false;
		for(i=0;i<10;i++)
			if(m_byChessBoard[i][nFromX-1]==B_CANON && i!=nFromY-1 && i!=nToY-1)
			{
				bIsAgain=true;
				break;
			}
			
			if(nFromY>nToY)
			{
				if(bIsAgain)
				{
					if(i>nFromY-1)
						str.Format("�ڣ����ڽ�%d",nFromY-nToY);
					else
						str.Format("�ڣ�ǰ�ڽ�%d",nFromY-nToY);
				}
				else
					str.Format("�ڣ���%d��%d",nFromX,nFromY-nToY);
			}
			else
				if(nFromY<nToY)
				{
					bIsAgain=false;
					for(i=0;i<10;i++)
						if(m_byChessBoard[i][nFromX-1]==B_CANON && i!=nFromY-1 && i!=nToY-1)
						{
							bIsAgain=true;
							break;
						}
						
						if(bIsAgain)
						{
							if(i>nFromY-1)
								str.Format("�ڣ����ڽ�%d",nToY-nFromY);
							else
								str.Format("�ڣ�ǰ�ڽ�%d",nToY-nFromY);
						}
						else
							str.Format("�ڣ���%d��%d",nFromX,nToY-nFromY);
				}
				else
				{
					if(bIsAgain)
					{
						if(i>nFromY-1)
							str.Format("�ڣ�����ƽ%d",nToX);
						else
							str.Format("�ڣ�ǰ��ƽ%d",nToX);
					}
					else
						str.Format("�ڣ���%dƽ%d",nFromX,nToX);
					break;
				}
				
				break;
				
	case B_BISHOP://��ʿ
		if(nFromY>nToY)
			str.Format("�ڣ�ʿ%d��%d",nFromX,nToX);
		else
			str.Format("�ڣ�ʿ%d��%d",nFromX,nToX);
		
		break;
		
	case B_ELEPHANT://����
		bIsAgain=false;
		for(i=0;i<5;i++)
			if(m_byChessBoard[i][nFromX-1]==B_ELEPHANT && i!=nFromY-1 && i!=nToY-1)
			{
				bIsAgain=true;
				break;
			}
			
			if(bIsAgain)
			{
				if(i>nFromY-1)
				{
					if(nFromY>nToY)
						str.Format("�ڣ�������%d",nToX);
					else
						str.Format("�ڣ������%d",nToX);
				}
				else
				{
					if(nFromY>nToY)
						str.Format("�ڣ�ǰ����%d",nToX);
					else
						str.Format("�ڣ�ǰ���%d",nToX);
				}
			}
			else
			{
				if(nFromY>nToY)
					str.Format("�ڣ���%d��%d",nFromX,nToX);
				else
					str.Format("�ڣ���%d��%d",nFromX,nToX);
			}
			
			break;
			
	case B_PAWN://����
		nCount=0;
		j=0;
		for(i=0;i<5;i++)
			nPos[i]=-1;
		
		for(i=0;i<10;i++)
			if(m_byChessBoard[i][nFromX-1]==B_PAWN && i!=nFromY-1 && i!=nToY-1)
			{
				nPos[j]=i;
				nCount++;
			}
			
			if(nCount==0)
			{
				if(nFromY==nToY)
					str.Format("�ڣ���%dƽ%d",nFromX,nToX);
				else
					str.Format("�ڣ���%d��%d",nFromX,1);
				
				break;
			}
			if(nCount==1)
			{
				if(nFromY>nPos[0])
				{
					if(nFromY==nToY)
						str.Format("�ڣ�ǰ��ƽ%d",nToX);
					else
						str.Format("�ڣ�ǰ���%d",1);
				}
				else
				{
					if(nFromY==nToY)
						str.Format("�ڣ�����ƽ%d",nToX);
					else
						str.Format("�ڣ������%d",1);
				}
				
				break;
			}
			j=0;
			if(nCount>1)
			{
				for(i=0;i<5;i++)
					if(nPos[i]==-1)
						break;
					else
						if(nPos[i]>nFromY)
							break;
						else
							j++;
						
						if(nFromY==nToY)
							str.Format("�ڣ�%d��ƽ%d",j+1,1);
						else
							str.Format("�ڣ�%d���%d",j+1,1);
						
						break;
			}
			
	case R_KING://��˧
		if(nFromX==nToX)
		{
			if(nFromY>nToY)
				str="�죺˧"+ConvertDigit2Chinese(10-nFromX)+"��"+ConvertDigit2Chinese(nFromY-nToY);
			else
				str="�죺˧"+ConvertDigit2Chinese(10-nFromX)+"��"+ConvertDigit2Chinese(nToY-nFromY);
		}
		else
			str="�죺˧"+ConvertDigit2Chinese(10-nFromX)+"ƽ"+ConvertDigit2Chinese(10-nToX);
		
		break;
		
	case R_CAR://�쳵
		bIsAgain=false;
		for(i=0;i<10;i++)
			if(m_byChessBoard[i][nFromX-1]==R_CAR && i!=nFromY-1 && i!=nToY-1)
			{
				bIsAgain=true;
				break;
			}
			
			if(nFromY>nToY)
			{
				if(bIsAgain)
				{
					if(i>nFromY-1)
						str="�죺ǰ����"+ConvertDigit2Chinese(nFromY-nToY);
					else
						str="�죺�󳵽�"+ConvertDigit2Chinese(nFromY-nToY);
				}
				else
					str="�죺��"+ConvertDigit2Chinese(10-nFromX)+"��"+ConvertDigit2Chinese(nFromY-nToY);
			}
			else
				if(nFromY<nToY)
				{
					if(bIsAgain)
					{
						if(i>nFromY-1)
							str="�죺����"+ConvertDigit2Chinese(nToY-nFromY);
						else
							str="�죺ǰ����"+ConvertDigit2Chinese(nToY-nFromY);
					}
					else
						str="�죺��"+ConvertDigit2Chinese(10-nFromX)+"��"+ConvertDigit2Chinese(nToY-nFromY);
				}
				else
				{
					if(bIsAgain)
					{
						if(i>nFromY-1)
							str="�죺��ƽ"+ConvertDigit2Chinese(nToX);
						else
							str="�죺ǰ��ƽ"+ConvertDigit2Chinese(nToX);
					}
					else
						str="�죺��"+ConvertDigit2Chinese(10-nFromX)+"ƽ"+ConvertDigit2Chinese(10-nToX);
					
					break;
				}
				
				break;
				
	case R_HORSE://����
		bIsAgain=false;
		for(i=0;i<10;i++)
			if(m_byChessBoard[i][nFromX-1]==R_HORSE && i!=nFromY-1 && i!=nToY-1)
			{
				bIsAgain=true;
				break;
			}
			
			if(bIsAgain)
			{
				if(i>nFromY-1)
				{
					if(nFromY>nToY)
						str="�죺ǰ���"+ConvertDigit2Chinese(10-nToX);
					else
						str="�죺ǰ����"+ConvertDigit2Chinese(10-nToX);
				}
				else
				{
					if(nFromY>nToY)
						str="�죺ǰ���"+ConvertDigit2Chinese(10-nToX);
					else
						str="�죺ǰ����"+ConvertDigit2Chinese(10-nToX);
				}
			}
			else
			{
				if(nFromY>nToY)
					str="�죺��"+ConvertDigit2Chinese(10-nFromX)+"��"+ConvertDigit2Chinese(10-nToX);
				else
					str="�죺��"+ConvertDigit2Chinese(10-nFromX)+"��"+ConvertDigit2Chinese(10-nToX);
			}
			
			break;
			
	case R_CANON://����
		bIsAgain=false;
		for(i=0;i<10;i++)
			if(m_byChessBoard[i][nFromX-1]==R_CANON && i!=nFromY-1 && i!=nToY-1)
			{
				bIsAgain=true;
				break;
			}				
			
			if(nFromY>nToY)
			{
				if(bIsAgain)
				{
					if(i>nFromY-1)
						str="�죺ǰ�ڽ�"+ConvertDigit2Chinese(nFromY-nToY);
					else
						str="�죺���ڽ�"+ConvertDigit2Chinese(nFromY-nToY);
				}
				else
					str="�죺��"+ConvertDigit2Chinese(10-nFromX)+"��"+ConvertDigit2Chinese(nFromY-nToY);
			}
			else
				if(nFromY<nToY)
				{
					if(bIsAgain)
					{
						if(i>nFromY-1)
							str="�죺ǰ����"+ConvertDigit2Chinese(nToY-nFromY);
						else
							str="�죺������"+ConvertDigit2Chinese(nToY-nFromY);
					}
					else
						str="�죺��"+ConvertDigit2Chinese(nFromX)+"��"+ConvertDigit2Chinese(nToY-nFromY);
				}
				else
				{
					if(bIsAgain)
					{
						if(i>nFromY-1)
							str="�죺ǰ��ƽ"+ConvertDigit2Chinese(10-nToX);
						else
							str="�죺����ƽ"+ConvertDigit2Chinese(10-nToX);
					}
					else
						str="�죺��"+ConvertDigit2Chinese(10-nFromX)+"ƽ"+ConvertDigit2Chinese(10-nToX);
				}
				
				break;
				
	case R_BISHOP://��ʿ
		if(nFromY>nToY)
			str="�죺ʿ"+ConvertDigit2Chinese(10-nFromX)+"��"+ConvertDigit2Chinese(10-nToX);
		else
			str="�죺ʿ"+ConvertDigit2Chinese(10-nFromX)+"��"+ConvertDigit2Chinese(10-nToX);
		
		break;
		
	case R_ELEPHANT://����
		bIsAgain=false;
		for(i=0;i<5;i++)
			if(m_byChessBoard[i][nFromX-1]==R_ELEPHANT && i!=nFromY-1 && i!=nToY-1)
			{
				bIsAgain=true;
				break;
			}
			
			if(bIsAgain)
			{
				if(i>nFromY-1)
				{
					if(nFromY>nToY)
						str="�죺ǰ����"+ConvertDigit2Chinese(10-nToX);
					else
						str="�죺ǰ���"+ConvertDigit2Chinese(10-nToX);
				}
				else
				{
					if(nFromY>nToY)
						str="�죺������"+ConvertDigit2Chinese(10-nToX);
					else
						str="�죺�����"+ConvertDigit2Chinese(10-nToX);
				}
			}
			else
			{
				if(nFromY>nToY)
					str="�죺��"+ConvertDigit2Chinese(10-nFromX)+"��"+ConvertDigit2Chinese(10-nToX);
				else
					str="�죺��"+ConvertDigit2Chinese(10-nFromX)+"��"+ConvertDigit2Chinese(10-nToX);
			}
			
			break;
			
	case R_PAWN://���
		nCount=0;
		j=0;
		for(i=0;i<5;i++)
			nPos[i]=-1;
		
		for(i=0;i<10;i++)
			if(m_byChessBoard[i][nFromX-1]==R_PAWN && i!=nFromY-1 && i!=nToY-1)
			{
				nPos[j]=i;
				nCount++;
			}
			
			if(nCount==0)
			{
				if(nFromY==nToY)
					str="�죺��"+ConvertDigit2Chinese(10-nFromX)+"ƽ"+ConvertDigit2Chinese(10-nToX);
				else
					str="�죺��"+ConvertDigit2Chinese(10-nFromX)+"��"+ConvertDigit2Chinese(1);
				
				break;
			}
			if(nCount==1)
			{
				if(nFromY-1>nPos[0])
				{
					if(nFromY==nToY)
						str="�죺ǰ��ƽ"+ConvertDigit2Chinese(10-nToX);
					else
						str="�죺ǰ����"+ConvertDigit2Chinese(1);
				}
				else
				{
					if(nFromY==nToY)
						str="�죺���ƽ"+ConvertDigit2Chinese(10-nToX);
					else
						str="�죺�����"+ConvertDigit2Chinese(1);
				}
				
				break;
			}
			j=0;
			if(nCount>1)
			{
				for(i=0;i<5;i++)
					if(nPos[i]==-1)
						break;
					else
						if(nPos[i]>nFromY-1)
							break;
						else
							j++;
						if(nFromY==nToY)
							str="�죺"+ConvertDigit2Chinese(j+1)+"��ƽ"+ConvertDigit2Chinese(nToX);
						else
							str="�죺"+ConvertDigit2Chinese(j+1)+"����"+ConvertDigit2Chinese(1);	
			}
			
			break;
			
	default:
		break;
	}

	return str;
}
void CChessDlg::OnDblclkListchessrecord() 
{
	// TODO: Add your control notification handler code here
	int nSel=m_lstChessRecord.GetCurSel();
	int nNum=m_lstChessRecord.GetCount();
	int nCount=0;

	while(nCount<nNum-nSel)
	{
		this->OnBtnundo();
		nCount+=2;
	}
}

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_btnOk.SetBitmap(m_bitmapOk);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChessDlg::Think()
{
	int timecount;
	CString sNodeCount;
	
	timecount=GetTickCount();//ȡ��ʼʱ��
	m_staticTip.SetWindowText("������˼�����������...");
	
	if(m_nUserChessColor==BLACKCHESS)
		m_iBout++;
	m_bIsThinking=true;

	m_pSE->SearchAGoodMove(m_byChessBoard);   ///...
	memcpy(m_byShowChessBoard,m_byChessBoard,90);
	memcpy(m_byBackupChessBoard,m_byChessBoard,90);
	m_cmBestMove=m_pSE->GetBestMove();//�õ�����߷�
	m_umUndoMove=m_pSE->GetUndoMove();
	m_stackUndoMove.push(m_umUndoMove);//�������߷�ѹջ
	this->AddChessRecord(m_cmBestMove.From.x+1,m_cmBestMove.From.y+1,m_cmBestMove.To.x+1,m_cmBestMove.To.y+1,m_nUserChessColor,m_cmBestMove.nChessID);
	m_bIsThinking=false;
	
	//�ػ���Ļ  
	InvalidateRect(NULL,FALSE);
	UpdateWindow();

	sNodeCount.Format("������%d���ڵ�,����ʱ��%.3fs",m_pEvel->GetAccessCount(),(GetTickCount()-timecount)/1000.0);
	m_staticTip.SetWindowText(sNodeCount);

	::FlashWindow(this->GetSafeHwnd(),TRUE);
	m_btnStop.EnableWindow(0);

	m_pEvel->ClearAccessCount();
	
	switch(IsGameOver(m_byChessBoard))
	{
	case -1:
		m_staticTip.SetWindowText("����,���ǿŶ");
		break;

	case 1:
		m_staticTip.SetWindowText("����,�����㲻���ҵĶ��ְ�");
		break;

	default:
		return;
	}
	
	m_bIsGameOver=true;
}

BOOL CChessDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	m_tooltip.RelayEvent(pMsg); 

	return CDialog::PreTranslateMessage(pMsg);
}

void CChessDlg::OnBtnStop() 
{
	// TODO: Add your control notification handler code here
	::TerminateThread(m_hHandle,0);
	::WaitForSingleObject(m_hHandle,INFINITE);
	::CloseHandle(m_hHandle);

	m_btnStop.EnableWindow(0);
	m_bIsThinking=0;
	m_progressThink.SetPos(0);
	m_staticTip.SetWindowText("�ҵ�˼���ѱ�����");

	//�����û��߷�
	memcpy(m_byShowChessBoard,m_byBackupChessBoard,90);
	memcpy(m_byChessBoard,m_byBackupChessBoard,90);
	m_stackUndoMove.pop();
	m_lstChessRecord.DeleteString(m_lstChessRecord.GetCount()-1);
	m_iBout--;

	//�ػ���Ļ  
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
}

void CChessDlg::OnSelchangeListchessrecord() 
{
	// TODO: Add your control notification handler code here
	if(m_Status!=Previewing)
	{
		m_staticTip.SetWindowText("��Ҫ��鿴��ǰ�ľ���Ļ�,�뵯���Ҽ��˵��㡰Ԥ����");
		return;
	}

	int nSel=m_lstChessRecord.GetCurSel();
	int nNum=m_lstChessRecord.GetCount();
	int nCount=0;

	if(!nNum)
		return;

	m_btnRedo.EnableWindow(1);//���ԭ��ť
	m_bIsGameOver=false;
	memcpy(m_byShowChessBoard,m_byChessBoard,90);
	while(nCount<nNum-nSel)
	{
		for(int i=0;i<2;i++)
		{
			m_umUndoMove=m_stackUndoMove.top();
			m_stackRedoMove.push(m_umUndoMove);
			m_pSE->UndoChessMove(m_byShowChessBoard,&m_umUndoMove.cmChessMove,m_umUndoMove.nChessID);
			memcpy(m_byBackupChessBoard,m_byShowChessBoard,90);
			m_stackUndoMove.pop();
			
			//�ػ���Ļ  
			InvalidateRect(NULL,FALSE);
			UpdateWindow();
		}

		nCount+=2;
	}

	//��ԭջm_stackUndoMove��m_stackRedoMove
	while(nCount)
	{
		for(int i=0;i<2;i++)
		{
			m_stackUndoMove.push(m_stackRedoMove.top());
			m_stackRedoMove.pop();
		}

		nCount-=2;
	}
}

void CChessDlg::OnPreview() 
{
	// TODO: Add your command handler code here
	m_Status=Previewing;
}

void CChessDlg::OnPreviewover() 
{
	// TODO: Add your command handler code here
	m_Status=Chessing;
	memcpy(m_byShowChessBoard,m_byChessBoard,90);
	m_staticTip.SetWindowText("�Ǻ�,��������״̬,������¿�");

	//�ػ���Ļ  
	InvalidateRect(NULL,FALSE);
	UpdateWindow();	
}

void CChessDlg::WinHelp(DWORD dwData, UINT nCmd) 
{
	// TODO: Add your specialized code here and/or call the base class
	CHelpDlg dlg;
	dlg.DoModal();
//	CDialog::WinHelp(dwData, nCmd);
}

void CChessDlg::OnHelp() 
{
	// TODO: Add your command handler code here
	CHelpDlg dlg;
	dlg.DoModal();
}

void CChessDlg::OnInversecb() 
{
	// TODO: Add your command handler code here
	this->InvertChessBoard(m_byShowChessBoard);

	//�ػ���Ļ  
	InvalidateRect(NULL,FALSE);
	UpdateWindow();	
}
