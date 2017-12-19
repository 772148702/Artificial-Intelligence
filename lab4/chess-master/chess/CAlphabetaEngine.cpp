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
	if (curAlpha != -20000) {//����alphabeta����
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

	/*i = IsGameOver(CurMap, nDepth);//����Ƿ���Ϸ����
	if (i != 0)
		return i;//���������ع�ֵ*/

				 //Ҷ�ӽڵ�ȡ��ֵ
	if (nDepth == 0)
		return m_pEval->Evaluate(CurMap, (m_nMaxDepth - nDepth) % 2);

	//�˺����ҳ���ǰ�������п��ܵ��߷���Ȼ��Ž�m_pMG ->m_MoveList����
	Count = m_pMG->AllValidMove(CurMap, nDepth, (m_nMaxDepth - nDepth) % 2);
	if (nDepth == m_nMaxDepth)
	{
		//�ڸ��ڵ��趨������
		pAi->SetRange(0, Count);
		pAi->SetStep(1);
	}
	//�����п��ܵ��߷�
	for (i = 0; i < Count; i++)
	{
		if (nDepth == m_nMaxDepth) 
			pAi->StepIt();//�߽�����
		type = MakeMove(&(m_pMG->MoveList[nDepth][i]));  //����ǰ����Ӧ�ô��߷�����Ϊ�ӽڵ�ľ���
		score = -AlphaBeta(nDepth - 1, -beta, -alpha);       //�ݹ������ӽڵ�
		UnMakeMove(&(m_pMG->MoveList[nDepth][i]), type);//���˽ڵ�ľ���ָ�Ϊ��ǰ�ڵ�
		if (score >= beta) {
			return beta;
		}
		if (score > alpha)
		{
			alpha = score;//��������ֵ
						  //�������ڵ�ʱ��������߷�
			if (nDepth == m_nMaxDepth)
				m_cmBestMove = m_pMG->MoveList[nDepth][i];
		}
		/*if (alpha >= beta)
			break;//��֦����������ʣ�µĽڵ�*/
	}
	return alpha;//���ؼ���ֵ
}

int CAlphabetaEngine::GetAlpha()
{
	return curAlpha;
}


