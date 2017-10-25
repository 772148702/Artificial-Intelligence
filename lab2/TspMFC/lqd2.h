#pragma once
#include <vector>
#include <iostream>
using namespace std;


class lqd2
{
public:
	lqd2();
	~lqd2();
	const int maxn = 300;
	const double eps = 1e-8;
	int n;
	 double dist[300][300];
	
	inline int dcmp(const double &x) {
		if (x > eps) return 1;
		if (x < -eps) return -1;
		return 0;
	}
	inline bool randtest(const double &searchRatio) {
		return (double(rand()) / RAND_MAX) < searchRatio;
	}
	struct sol {
		vector <int> r;
		double cost;
	

		inline int getl(int w) {
			if (w == 0) return r[r.size() - 1];
			else return r[w - 1];
		}
		inline int getr(int w) {
			if (w + 1 == r.size()) return r[0];
			else return r[w + 1];
		}
		inline int del(int w,double dist[][300]) {
			vector <int> ::iterator it = r.begin() + w;
			int lw = getl(w), rw = getr(w), u = r[w];
			cost -= (dist[lw][u] + dist[u][rw]);
			cost += dist[lw][rw];
			r.erase(it);
			return u;
		}
		inline void ins(int w, int c, double dist[][300]) {
			r.push_back(c);
			for (int i = r.size() - 1; i != w; --i) swap(r[i - 1], r[i]);
			int lw = getl(w), rw = getr(w);
			cost += dist[lw][c] + dist[c][rw];
			cost -= dist[lw][rw];
		}
		void change(int w1, int w2, double dist[][300]) {
			int lw1 = getl(w1), rw1 = getr(w1), lw2 = getl(w2), rw2 = getr(w2);
			int u = r[w1], v = r[w2];
			double d1 = dist[lw1][u] + dist[u][rw1] + dist[lw2][v] + dist[v][rw2];
			if (rw1 == v) rw1 = u, lw2 = v; else
				if (lw1 == v) lw1 = u, rw2 = v;
			double d2 = dist[lw1][v] + dist[v][rw1] + dist[lw2][u] + dist[u][rw2];
			cost = cost - d1 + d2;
			swap(r[w1], r[w2]);
		}
		inline double calc(double dist[][300]) {
			cost = 0.0;
			for (int i = 0; i < r.size(); ++i) cost += dist[r[i]][getr(i)];
			return cost;
		}
		inline void show() {
			printf("cost = %.6lf\n", cost);
			for (int i = 0; i < r.size(); ++i) {
				printf("%d", r[i]);
				if (i + 1 != r.size()) printf("->");
				if (i % 15 == 0) puts("");
			}
			puts("");
		}
	};
	 sol s, s1, s2, bests,cur;
	void op1(sol &a, sol &b) {
		static double mincost;
		static int besti, bestj;
		mincost = 1e9; besti = bestj = 0;
		b = a;
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j) {
				if (!randtest(0.05)) continue;
				a.change(i, j,dist);
				if (dcmp(a.cost - mincost) < 0) {
					mincost = a.cost; besti = i, bestj = j;
				}
				a.change(i, j,dist);
			}
		if (mincost < 5e8) b.change(besti, bestj,dist);
	}
	void op2(sol &a, sol &b) {
		static double mincost;
		static int besti, bestj;
		mincost = 1e9; besti = bestj = 0;
		b = a;
		for (int i = 0; i < n; ++i) {
			int u = a.del(i,dist);
			for (int j = 0; j < a.r.size(); ++j) {
				if (i == j) continue;
				if (!randtest(0.05)) continue;
				a.ins(j, u,dist);
				if (dcmp(a.cost - mincost) < 0) {
					mincost = a.cost, besti = i, bestj = j;
				}
				a.del(j,dist);
			}
			a.ins(i, u,dist);
		}
		if (mincost < 5e8) {
			int u = b.del(besti,dist);
			b.ins(bestj, u,dist);
		}
	}
	vector<int> getcur() {
		return cur.r;
	}
	DWORD WINAPI SA() {
		
		s.r.clear(); for (int i = 1; i <= n; ++i) s.r.push_back(i); s.calc(dist);
		cur = s;
		bests = s;
		double T = s.cost * 0.5, alpha = 0.90;
		for (int iteration = 1; iteration <= 100 && dcmp(T) > 0; iteration++, T *= alpha) {
			for (int i = 1; i <= 5000; ++i) {
				op1(s, s1); op2(s, s2);
				if (dcmp(s2.cost - s1.cost) < 0) s1 = s2;
				double tc = s1.cost;
				assert(dcmp(tc - s1.calc(dist)) == 0);
				double dE = s1.cost - s.cost;
				if (dcmp(dE) < 0) {
					s = s1;
					if (dcmp(s1.cost - bests.cost) < 0) bests = s1;
				}
				else
					if (randtest(exp(-dE / T))) s = s1;
				cur = s;

			}
			printf("%d %lf %lf\n", iteration, T, bests.cost);
		}
		bests.show();
		return 0;
	}
	double x[300], y[300];
	void init(vector<double> xx,vector<double> yy) {
	    double dx, dy, t;
		n = xx.size() - 1;
		for (int i = 1; i <= n; ++i) {
			x[i] = xx[i];
			y[i] = yy[i];
		}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) {
				dx = x[i] - x[j]; dy = y[i] - y[j];
				dist[i][j] = sqrt(dx * dx + dy * dy);
			}
	
	}


};

