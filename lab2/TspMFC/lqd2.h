#pragma once
#include <vector>
#include <iostream>
using namespace std;
#define maxn 300

class lqd2
{
public:
	lqd2();
	~lqd2();
	const double eps = 1e-8;
	int n;
	bool isEnd = false;
	double alpha = 0.98;
	int InLoop = 1000;
	double tem;
	double dist[maxn][maxn];
	double x[maxn], y[maxn];
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
		inline void rev(int w1, int w2, double dist[][300]) {
			reverse(r.begin() + w1, r.begin() + w2 + 1);
			calc(dist);
		}
	
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
	};
	sol s, s1, s2, s3, bests, cur;
	void op1(sol &a, sol &b, int p) {
		static double mincost;
		static int besti, bestj;
		mincost = 1e9; besti = bestj = 0;
		b = a;
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j) {
				if (!randtest(0.01 * (50000 - p) / 50000)) continue;
				a.change(i, j,dist);
				if (dcmp(a.cost - mincost) < 0) {
					mincost = a.cost; besti = i, bestj = j;
				}
				a.change(i, j, dist);
			}
		if (mincost < 5e8) b.change(besti, bestj, dist);
	}
	void op2(sol &a, sol &b, int p) {
		static double mincost;
		static int besti, bestj;
		mincost = 1e9; besti = bestj = 0;
		b = a;
		for (int i = 0; i < n; ++i) {
			int u = a.del(i, dist);
			for (int j = 0; j < a.r.size(); ++j) {
				if (i == j) continue;
				if (!randtest(0.01 * (50000 - p) / 50000)) continue;
				a.ins(j, u, dist);
				if (dcmp(a.cost - mincost) < 0) {
					mincost = a.cost, besti = i, bestj = j;
				}
				a.del(j, dist);
			}
			a.ins(i, u, dist);
		}
		if (mincost < 5e8) {
			int u = b.del(besti, dist); b.ins(bestj, u, dist);
		}
	}
	void op3(sol &a, sol &b, int p) {
		static double mincost;
		static int besti, bestj;
		mincost = 1e9; besti = bestj = 0;
		b = a;
		for (int i = 0; i < n; ++i)
			for (int j = i + 1; j < n; ++j) {
				if (!randtest(0.005 * (50000 - p) / 50000)) continue;
				a.rev(i, j, dist);
				if (dcmp(a.cost - mincost) < 0) {
					mincost = a.cost; besti = i, bestj = j;
				}
				a.rev(i, j, dist);
			}
		if (mincost < 5e8) b.change(besti, bestj, dist);
	}
	void op4(sol &a, sol &b) {
		b = a;
		for (bool Found = true; Found;) {
			Found = false;
			double cost = b.cost;
			for (int i = 0; i < n && !Found; ++i)
				for (int j = 0; j < n && !Found; ++j) {
					double c1, c2;
					if (i == j || (i + 1) % n == j || (j + 1) % n == i) continue;
					b.change((i + 1) % n, (j + 1) % n, dist); c1 = b.cost; b.change((i + 1) % n, (j + 1) % n, dist);
					b.change((i + 1) % n, j, dist); c2 = b.cost; b.change((i + 1) % n, j, dist);
					if (dcmp(c1 - cost) < 0) {
						Found = true; b.change((i + 1) % n, (j + 1) % n,dist);
					}
					else
						if (dcmp(c2 - cost) < 0) {
							Found = true; b.change((i + 1) % n, j, dist);
						}
				}
		}
	}
	vector<int> getcur() {
		return bests.r;
	}
	double get_cost() {
		return bests.cost;
	}
	double getTem() {
		return tem;
	}
	void localsearch() {
		isEnd = false;
		s.r.clear(); for (int i = 1; i <= n; ++i) s.r.push_back(i); s.calc(dist);
		bests = s;
		tem = 0;
		for (int iteration = 50000, baditeration = 0; iteration; --iteration) {
			op1(s, s1, iteration);
			op2(s, s2, iteration);
			//op3(s, s3);
			if (dcmp(s2.cost - s1.cost) < 0) s1 = s2;
			//if (dcmp(s3.cost - s1.cost) < 0) s1 = s3;
			if (dcmp(s1.cost - bests.cost) < 0) bests = s1;
			if (dcmp(s1.cost - s.cost) < 0) baditeration = 0; else baditeration++;
			s = s1;
			cur = s;
			if (baditeration % 10 == 0 && baditeration) {
				op4(s1, s);
				if (dcmp(s.cost - s1.cost) < 0) baditeration = 0;
			}
			if (isEnd == true) return;

		}
		s1 = bests; op4(s1, bests);
		isEnd = true;

	}
	void SA() {		
		isEnd = false;
		s.r.clear();
		for (int i = 1; i <= n; ++i) s.r.push_back(i);
		s.calc(dist);
		cur = s;
		bests = s;
		double T = s.cost * 0.5;
		tem = T;
		for (int iteration = 1; iteration <= 350 && dcmp(T) > 0; iteration++, T *= alpha, tem = T) {
			for (int i = 1; i <= InLoop; ++i) {
				op1(s, s1, i);
				op2(s, s2, i);
				//op3(s, s3, i);
				if (dcmp(s2.cost - s1.cost) < 0) s1 = s2;
				//if (dcmp(s3.cost - s1.cost) < 0) s1 = s3;
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
				if (isEnd == true) return;
			}
		}
		isEnd = true;
	}
	void init(vector<double> xx,vector<double> yy, double delta, int inner_Loop) {
		srand(time(NULL));
		alpha = delta;
		InLoop = inner_Loop;
		double dx, dy;
		n = xx.size() - 1;
		for (int i = 0; i <= n; ++i) {
			x[i] = xx[i];
			y[i] = yy[i];
		}
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) {
				dx = x[i] - x[j];
				dy = y[i] - y[j];
				dist[i][j] = sqrt(dx * dx + dy * dy);
			}
	}
};

