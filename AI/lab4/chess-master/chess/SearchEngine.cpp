#include "StdAfx.h"
#include "SearchEngine.h"


CSearchEngine::CSearchEngine(void)
{
}


CSearchEngine::~CSearchEngine(void)
{
}

int CSearchEngine::GetAlpha()
{
	return 0;
}

void CSearchEngine::SetAiProgressCtrl(CProgressCtrl * pAiP)
{
	pAi = pAiP;
}


int CSearchEngine::MakeMove(CHESSMOVE* move)
{
	int nChessID;
	nChessID = CurMap[move->to.x][move->to.y];
	CurMap[move->to.x][move->to.y] = CurMap[move->from.x][move->from.y];
	CurMap[move->from.x][move->from.y] = NOCHESS;
	return nChessID;
}

void CSearchEngine::UnMakeMove(CHESSMOVE *move,int type)
{
	CurMap[move->from.x][move->from.y] = CurMap[move->to.x][move->to.y];
	CurMap[move->to.x][move->to.y] = type;
}

int CSearchEngine::IsGameOver(int position[10][9], int nDepth)
{
	int i, j;
	BOOL RedLive = FALSE, BlackLive = FALSE;

	//检查红方九宫是否有帅
	for (i = 7; i<10; i++)
		for (j = 3; j<6; j++)
		{
			if (position[i][j] == B_KING)
				BlackLive = TRUE;
			if (position[i][j] == R_KING)
				RedLive = TRUE;
		}

	//检查黑方九宫是否有将
	for (i = 0; i<3; i++)
		for (j = 3; j<6; j++)
		{
			if (position[i][j] == B_KING)
				BlackLive = TRUE;
			if (position[i][j] == R_KING)
				RedLive = TRUE;
		}

	i = (m_nMaxDepth - nDepth + 1) % 2;//取当前奇偶标志,奇数层为电脑方,偶数层为用户方
									   //红方不在
	if (!RedLive)
		if (i)
			return 19990 + nDepth; //奇数层返回极大值
		else
			return -19990 - nDepth;//偶数层返回极小值

								   //黑方不在
	if (!BlackLive)
		if (i)
			return -19990 - nDepth;//奇数层返回极小值
		else
			return 19990 + nDepth; //偶数层返回极大值

	return 0;//将帅都在，返回0
}
