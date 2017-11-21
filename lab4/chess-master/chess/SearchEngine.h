#pragma once
#include "Evaluation.h"
#include "MoveGenerater.h"
#include "global.h"

class CSearchEngine
{
public:
	typedef MoveStep CHESSMOVE;
	CSearchEngine(void);
	~CSearchEngine(void);
	virtual CHESSMOVE SearchAGoodMove(int Map[10][9])=0;
	void SetAiProgressCtrl(CProgressCtrl* pAiP);
	void SetSearchDepth(int nDepth) {
		m_nSearchDepth = nDepth;
	}
	void SetEvaluator(CEvaluation* pEval) {
		m_pEval = pEval;
	}
	void SetMoveGenerator(CMoveGenerater* pMG) {
		m_pMG = pMG;
	}
protected:
	virtual int MakeMove(CHESSMOVE *move);
	virtual void UnMakeMove(CHESSMOVE*move,int type);
	int IsGameOver(int position[10][9], int nDepth);
	CHESSMOVE m_cmBestMove;
	int CurMap[10][9];
	CEvaluation * m_pEval;
	CMoveGenerater *m_pMG;
	CProgressCtrl* pAi;
	int m_nSearchDepth;
	int m_nMaxDepth;
};

