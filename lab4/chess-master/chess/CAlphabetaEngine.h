#pragma once
#include "SearchEngine.h"
class CAlphabetaEngine :
	public CSearchEngine
{
public:
	CAlphabetaEngine();
	~CAlphabetaEngine();
	MoveStep SearchAGoodMove(int position[10][9]);//供界面调用的接口，为当前局面产生一步好棋
	int AlphaBeta(int depth, int alpha, int beta);//alpha-beta的搜索函数
};

