#pragma once
#include "SearchEngine.h"
class CAlphabetaEngine :
	public CSearchEngine
{
public:
	CAlphabetaEngine();
	~CAlphabetaEngine();
	MoveStep SearchAGoodMove(int position[10][9]);//��������õĽӿڣ�Ϊ��ǰ�������һ������
	int AlphaBeta(int depth, int alpha, int beta);//alpha-beta����������
};

