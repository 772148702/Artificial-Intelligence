#pragma once
#include <vector>
#include <map>
#include "state.h"
#include "stdafx.h"
using namespace std;
//路径从下标一开始



class ga
{
public:
	ga();
	~ga();
	vector<state> pool;
	int poolSize;
	int chooseNum; //每次循环的选取的交配的个体
	double jiaocha;
	double bianyi;
	vector<state> record;
	state curbest;
	state allbest;
	//跟新状态池，更新每种情况的可能性。
	void update() {
		double total = 0;
		int n = pool.size();
		for (auto st:pool) {
			st.value = 100000 / st.cost;  //每个个体适应值的计算
			total += st.value;
		}
		double pre = 0;
		for (auto st : pool) {
			st.accPro = pre + st.value/total; //前序概率的计算
			pre  = st.accPro;
		}
	}
	//轮盘旋转得到父母的索引。
	void getPM(int& ii) {
		    ii =  0;
			srand(time(0));
			double p1 = 0;
			p1 = double(rand()) / RAND_MAX;
			int len = pool.size();
			for (int i = 0; i < len; i++) {
				if (pool[i].accPro >= p1) {
					ii = i;
					break;
				}
			}
			return;
		
	}
	vector<int> getRandWay(int n) {
		srand(time(0));
		map<int, int> vis;
		int cnt = 1;
		vector<int> way;
		while (cnt <= n) {
			int lo = rand() % (n + 1);
			if (lo == 0) lo = 1;
			if (vis.count(lo) == 0) {
				way.push_back(lo);
				vis[lo] = 1;
				cnt++;
			}
		}
		return way;
	}
	void init(vector<double>& x,vector<double>&y) {
		poolSize = 3000;
		chooseNum = 3000;
		int lenn = x.size();  //包含了0
		state::setdis(&x, &y);
		allbest = curbest = state(getRandWay(lenn - 1));
		double vc = INT_MAX;
		for (int i = 1; i <= poolSize; i++) {
			vector<int> way = getRandWay(lenn-1);
			state tmp = state(way);
			pool.push_back(tmp);
			if (tmp.cost < vc) {
			   vc = tmp.cost;
			   curbest = tmp;
			}
		
		}
		if (allbest.cost < curbest.cost) allbest = curbest;
		record.push_back(curbest);
	}
	//进化函数
	void evaluation() {
		//外循环的次数可以改进
		for (int i = 0; i < 1000; i++) {
			//更新各个个体的适应值，以及前序概率和
			for (auto st : pool)
			{
				st.calCost();
			}
			this->update();
			//赌轮盘旋转方法，选取样本。
			vector<state> newPool;
			for (int i = 0; i < chooseNum; i++) {
				int h;
				getPM(h);
				state tmp = pool[h];
				newPool.push_back(tmp);
			}
			vector<state> newGeneration;
			vector<int> tmp1, tmp2;
			for (int i = 0; i < chooseNum -1; i=i+2) {
				//遗传
				Cross(newPool[i].way, newPool[i + 1].way, tmp1, tmp2);
				newGeneration.push_back(tmp1);
				newGeneration.push_back(tmp2);
				

				//变异
			}
			pool = newGeneration;
		}

	}
	void Cross(vector<int>  pa, vector<int> mo, vector<int>& s1, vector<int> & s2) {
		int len = mo.size();
		vector<int> tmp1 = pa, tmp2 = mo;
		for (int i = 1; i < len - 1; i++) {
			double tmp = double(rand()) / RAND_MAX;
			if (tmp < jiaocha) {
				cross1(tmp1, tmp2, i, s1, s2);
				tmp1 = s1;
				tmp2 = s2;
			}
		}
	}
	//在位置发生交叉产生两个后代。
	void cross1(vector<int>  pa, vector<int> mo,int lo,vector<int>& s1,vector<int> & s2) {
		map<int, int> vis1;
		map<int, int> vis2;
		for (int i = 0; i < lo; i++) {
			vis1[pa[i]] = i;
			vis2[mo[i]] = i;
		}
		vector<int> v1, v2;
		//完成了交换，只需要对i<lo的位置进行去重了。
		s1 = mo;
		s2 = pa;
		for (int i = 0; i < lo; i++) {
			if (vis2[pa[i]] == 0) {
				v1.push_back(pa[i]);
			}
			if (vis1[mo[i]] == 0) {
				v2.push_back(mo[i]);
			}
		}
		//需要一个映射关系来去重。
		map<int, int> change;
		for (int i = 0; i < v1.size(); i++)
		{
			change[v1[i]] = v2[i];
			change[v2[i]] = v1[i];
		}
		
		for (int i = 0; i < lo; i++) {
			if (change[pa[i]] != 0) {
				s1[i] = change[pa[i]];
			}
			if (change[mo[i]] != 0) {
				s2[i] = change[mo[i]];
			}
		}
	}
};

