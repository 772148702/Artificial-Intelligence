#pragma once
#include <vector>
#include <map>
using namespace std;
struct state {
	vector<int> way;
	double cost;
	static  vector <vector<double >>  dis;
	double accPro; //累加的概率
	double value;
	static void setdis(vector<double>* x, vector<double>* y) {
		int len = x->size() + 1; //start from 1
		
		dis.resize(len);
		for (int i = 1; i < len; i++) {
			dis[i].resize(len);
		}
		for (int i = 1; i < len; i++)
			for (int j = 1; j < len; j++) {
				dis[i][j] = sqrt(((*x)[i] - (*x)[j])*((*x)[i] - (*x)[j]) + ((*y)[i] - (*y)[j])*((*y)[i] - (*y)[j]));
			}
	}
	state(vector<int> n_way) {
		this->way = n_way;
		cost = calCost();

	}
	state() {


	}
	double calCost() {
		double ans = 0;
		//tmp 的下标是从0开始的，而x中的下表是从1开始的
		int len = way.size();

		for (int i = 0; i < len - 1; i++) {
			ans += (dis)[way[i]][way[i + 1]];
		}
		return ans;
	}
};


