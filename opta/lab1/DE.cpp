#include "stdafx.h"
#include "DE.h"

#include <WINDOWS.H>    
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <ctime>
#include <cstdlib>

#include "testfunc.h"
inline double randf() {
	return 1.0 * rand() / RAND_MAX;
}
inline int randint(int x) {
	static int ret;
	ret = randf() * x;
	if (ret >= x) ret = x - 1; if (ret < 0) ret = 0;
	return ret;
}
double *OShift, *M, *y, *z, *x_bound, f[2];
int ini_flag = 0, n_flag, func_flag, *SS;

int D = 10;//函数维度 
double xmin = -100.0, xmax = 100.0;
int funcnum[4] = { 1, 4, 11, 21 };//测试函数编号 

int m = (int)(D * 7.5);//种群规模
double F = 0.5;//缩放因子
double CR = 0.3;//交叉概率
double x[750][120], xx[750][120], X[120], trail[120], cost[750];

void work(int id,vector<double>& ans) {
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < D; ++j) x[i][j] = randf() * (xmax - xmin) + xmin;
		for (int j = 0; j < D; ++j) X[j] = x[i][j];
		TestFunc().cec17_test_func(X, f, D, 1, id); cost[i] = f[0];
	}
	
	double flag = DBL_MAX;
	for (int iter = 0; iter < 1000; ++iter) {
		flag = DBL_MAX;
		for (int i = 0; i < m; ++i) {
			int a = randint(m), b = randint(m), c = randint(m);
			while (b == a) b = randint(m);
			while (c == a || c == b) c = randint(m);
			int j = randint(D);
			for (int k = 1; k <= D; ++k, j = (j + 1) % D)
				if (randf() < CR || k == D) trail[j] = x[c][j] + F * (x[a][j] - x[b][j]);
				else trail[j] = x[i][j];
				for (int k = 0; k < D; ++k) X[k] = trail[k];
				TestFunc().cec17_test_func(X, f, D, 1, id);
				double score = f[0];
				if (score <= cost[i]) {
					for (int k = 0; k < D; ++k) xx[i][k] = trail[k];
					cost[i] = score;
				}
				else {
					for (int k = 0; k < D; ++k) xx[i][k] = x[i][k];
				}
				if (cost[i] < flag) {
					flag = cost[i];
				}
				
		}
		ans.push_back(flag);
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < D; ++j) x[i][j] = xx[i][j];
	}
	double minv = 1e18;
	int best = -1;
	for (int i = 0; i < m; ++i)
		if (cost[i] < minv) minv = cost[i], best = i;
	//printf("%lf\n", minv);
	//printf("x[] = ");
	//for (int i = 0; i < D; ++i) printf(" %.2lf", x[best][i]);
	//puts("");

}

void DE::run(int _id) {
	ans.resize(0);
	work(_id, ans);
}
vector<double> DE::getResult() {
	
	return  ans;
}

DE::DE()
{
}


DE::~DE()
{
}
