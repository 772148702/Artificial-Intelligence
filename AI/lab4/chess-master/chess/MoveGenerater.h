#pragma once

#include <vector>
#include "global.h"
using namespace std;

class CMoveGenerater
{
public:
	CMoveGenerater(void);
	~CMoveGenerater(void);
	static bool IsValidMove(int Map[10][9],const CPoint &From,const CPoint &To);
	int AllValidMove(int Map[10][9],int ply,int size);
	MoveStep MoveList[8][80];
protected:
	int m_nMoveCount;
	//将产生的走法插入到M_MoveList中去！！！！！！！！！！
	inline void AddMove(MoveStep p , int ply);
	//下面规定所有棋子的走法！！！！
	//黑将
	void GNT_BJiangMove(int Map[10][9] ,CPoint &pos , int nPly);
	//红帅
	void GNT_RShuaiMove(int Map[10][9] , CPoint &pos , int nPly);
	//黑士
	void GNT_BShiMove(int Map[10][9], CPoint &pos, int nPly);
	//红士
	void GNT_RShiMove(int Map[10][9], CPoint &pos, int nPly);
	//相
	void GNT_XiangMove(int Map[10][9] , CPoint &pos , int nPly);
	//马
	void GNT_MaMove(int Map[10][9] , CPoint &pos , int nPly);
	//車
	void GNT_JuMove(int Map[10][9] , CPoint &pos , int nPly);
	//炮
	void GNT_PaoMove(int Map[10][9], CPoint &pos, int nPly);
	//红兵
	void GNT_RBingMove(int Map[10][9], CPoint &pos, int nPly);
	//黑卒
	void GNT_BZuMove(int Map[10][9] , CPoint &pos , int nPly);
};

