#include "stdafx.h"
#include "CAlphabetaEngine.h"

CAlphabetaEngine::CAlphabetaEngine()
{
}


CAlphabetaEngine::~CAlphabetaEngine()
{
}

MoveStep CAlphabetaEngine::SearchAGoodMove(int Map[10][9])
{
	m_nMaxDepth = m_nSearchDepth;
	memcpy(CurMap, Map, 90 * sizeof(int));
	curAlpha = AlphaBeta(m_nMaxDepth, -20000, 20000);
	if (curAlpha != -20000) {//进行alphabeta搜索
		MakeMove(&m_cmBestMove);
		return m_cmBestMove;
	}
	return MoveStep(CPoint(0, 0), CPoint(0, 0), 0);
}

int CAlphabetaEngine::AlphaBeta(int nDepth, int alpha, int beta)
{
	int score;
	int Count, i;
	int type;

	/*i = IsGameOver(CurMap, nDepth);//检查是否游戏结束
	if (i != 0)
		return i;//结束，返回估值*/

				 //叶子节点取估值
	if (nDepth == 0)
		return m_pEval->Evaluate(CurMap, (m_nMaxDepth - nDepth) % 2);

	//此函数找出当前局面所有可能的走法，然后放进m_pMG ->m_MoveList当中
	Count = m_pMG->AllValidMove(CurMap, nDepth, (m_nMaxDepth - nDepth) % 2);
	if (nDepth == m_nMaxDepth)
	{
		//在根节点设定进度条
		pAi->SetRange(0, Count);
		pAi->SetStep(1);
	}
	//对所有可能的走法
	for (i = 0; i < Count; i++)
	{
		if (nDepth == m_nMaxDepth) 
			pAi->StepIt();//走进度条
		type = MakeMove(&(m_pMG->MoveList[nDepth][i]));  //将当前局面应用此走法，变为子节点的局面
		score = -AlphaBeta(nDepth - 1, -beta, -alpha);       //递归搜索子节点
		UnMakeMove(&(m_pMG->MoveList[nDepth][i]), type);//将此节点的局面恢复为当前节点
		if (score >= beta) {
			return beta;
		}
		if (score > alpha)
		{
			alpha = score;//保留极大值
						  //靠近根节点时保留最佳走法
			if (nDepth == m_nMaxDepth)
				m_cmBestMove = m_pMG->MoveList[nDepth][i];
		}
		/*if (alpha >= beta)
			break;//剪枝，放弃搜索剩下的节点*/
	}
	return alpha;//返回极大值
}

int CAlphabetaEngine::GetAlpha()
{
	return curAlpha;
}


