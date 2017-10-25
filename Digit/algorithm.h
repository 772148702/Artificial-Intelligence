#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include <set>
using namespace std;

class state {
	//st是棋盘上的棋子
public:
	vector<int> st;
	//r,c是0的位置
	int r, c;
	int fn, gn, hn;
	void init() {
	
		for (int i = 0; i < st.size(); i++)
		{
			if (st[i] == 0) {
				r = i / 3;
				c = i % 3;
				break;
			}
		}
	}
	void upDateHn() {
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

	void init(vector<int> tmp);
	state new_cur;
	queue <Record> record;
	bool run();
	priority_queue<state,vector<state>,CMP2> open;
	set<state,CMP1> close;

};

