#include "stdafx.h"
#include "PSO.h"

#include <WINDOWS.H>    
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <ctime>
#include <cstdlib>
#include "testfunc.h"
inline double pso_randf() {
	return 1.0 * rand() / RAND_MAX;
}

double  pso_f[2];


int pso_D = 10; //函数的维
int N = 40; //粒子数 
double c1 = 1.8, c2 = 1.8;//参数 
double pso_xmin = -100.0, pso_xmax = 100.0;

double gbestx[105], gbestf;

struct particle {
	double x[105], bestx[105];
	double f, bestf;
}swarm[50];

void  pso_work(int id,vector<double>& ans) {
	for (int i = 0; i < pso_D; ++i) gbestx[i] = pso_randf() * (pso_xmax - pso_xmin) + pso_xmin;
	TestFunc().cec17_test_func(gbestx, pso_f, pso_D, 1, id);
	gbestf = pso_f[0];

	double flag = DBL_MAX;

	for (int i = 0; i < N; ++i) {
		particle* p = &swarm[i];
		for (int j = 0; j < pso_D; ++j) p->x[j] = pso_randf() * (pso_xmax - pso_xmin) + pso_xmin;
		TestFunc().cec17_test_func(p->x, pso_f, pso_D, 1, id);
		p->f = p->bestf = pso_f[0];
	}

	for (int iter = 0; iter < 5000; ++iter) {
		flag = DBL_MAX;
		for (int i = 0; i < N; ++i) {
			particle* p = &swarm[i];
			for (int j = 0; j < pso_D; ++j) p->x[j] += c1 * pso_randf() * (p->bestx[j] - p->x[j])
				+ c2 * pso_randf() * (gbestx[j] - p->x[j]);
			TestFunc().cec17_test_func(p->x, pso_f, pso_D, 1, id);
			p->f = pso_f[0];
			if (p->f < p->bestf) {
				for (int j = 0; j < pso_D; ++j) p->bestx[j] = p->x[j];
				p->bestf = p->f;
			}
			if (p->f < gbestf) {
				for (int j = 0; j < pso_D; ++j) gbestx[j] = p->x[j];
				for (int j = 0; j < pso_D; ++j) p->x[j] = pso_randf() * (pso_xmax - pso_xmin) + pso_xmin;
				gbestf = p->f;
			}
			if (flag > pso_f[0]) flag = pso_f[0];
		}
		ans.push_back(flag);
	}

	printf("%lf\n", gbestf);
	printf("x[] = ");
	for (int i = 0; i < pso_D; ++i) printf(" %.2lf", gbestx[i]); puts("");
}
PSO::PSO()
{
}
void  PSO::run(int _id) {
	ans.resize(0);
	pso_work(_id, ans);
}
vector<double> PSO::getResult() {
	return ans;
}
PSO::~PSO()
{
}
