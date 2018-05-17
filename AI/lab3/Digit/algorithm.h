#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include "time.h"
#define   CLOCKS_PER_SEC ((clock_t)1000) 
using namespace std;

class state {
	//st是棋盘上的棋子
public:
	vector<int> st;
	//r,c是0的位置
	int r, c;
	int fn, gn, hn;
	int pre;
	void init() {
		for (int i = 0; i < st.size(); i++)
		{
			if (st[i] == 0) {
				r = i / 3;
				c = i % 3;
				break;
			}
		}
		pre = -1;
	}
	void upDateHn2() {  //hn的计算方法二
		hn = 0;
		int k[] = { 4,0,1,2,5,8,7,6,3 }; //数字所在位置的索引。
		for (int i = 0; i < st.size(); i++) {
			hn += abs(i - k[st[i]]); //位置i的数移动到对应位置的的距离。
		}
	}
	void upDateHn1() {   //hn的计算方法一
		hn = 0;
		if (st[0] != 1) hn++;
		if (st[1] != 2) hn++;
		if (st[2] != 3) hn++;
		if (st[3] != 8) hn++;
		if (st[4] != 0) hn++;
		if (st[5] != 4) hn++;
		if (st[6] != 7) hn++;
		if (st[7] != 6) hn++;
		if (st[8] != 5) hn++;
	}
	bool operator==(state rhy) {
		for (int i = 0; i < 9; i++)
			if (st[i] != rhy.st[i]) return false;
		return true;
	}
};
struct Record {
	state cur;
	int opensize;
	int closesize;
	Record(state st, int op, int cl) {
		cur = st;
		opensize = op;
		closesize = cl;
	}
};
struct CMP1{
	bool operator()(const state &p1,const state& p2) const {
		for (int i = 0; i < p1.st.size(); i++)
		{
			if (p1.st[i] < p2.st[i]) return true;
			if (p1.st[i] > p2.st[i]) return false;
		}
		return false;
	}
};
struct CMP2 {
	bool operator() (state p1, state p2) {
		return p1.fn > p2.fn;
	}
};

class algorithm
{
public:
	algorithm();
	~algorithm();
	clock_t start, end;
	void init1(vector<int> tmp);
	void init2(vector<int> a);
	state new_cur;
	vector <Record> record;
	bool run1();
	bool run2();
	priority_queue<state,vector<state>,CMP2> open;
	vector<state> close;
	stack<state> method;
};

