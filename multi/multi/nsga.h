#pragma once
//aim at calculation of DZLT1
//you can change DZLT1 into DZLTx(x = 1, 2, 3) for correspondent function 
#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

const double PI = acos(-1.0);
inline int dcmp(const double &x) {
	if (x > 1e-6) return 1; else  if (x < -1e-6) return -1; else return 0;
}
inline double randdouble() {
	return 1.0 * rand() / RAND_MAX;
}
inline double randdouble(const double &a, const double &b) {
	return randdouble() * (b - a) + a;
}
inline int randint(const int &a, const int &b) {
	static int ret;
	ret = randdouble() * (b - a) + a;
	if (ret < a) ret = a; if (ret >= b) ret = b - 1;
	return ret;
}
const double d1 = 1e-8, d2 = 1.0 - 1e-8;
const int D = 30;
const int popsize = 200; //种群大小
const int iteration = 1000; //迭代次数
double v2[iteration][popsize][3];

struct one {
	double v[D];
	vector <double> sp;
	int np, rank;
	double d, f[3];
	void init() {
		for (int i = 0; i < D; ++i) v[i] = randdouble();
		sp.clear();
	//	dtlz1(); //这个程序针对计算DTLZ1函数 
	}
	void cacul(int id, int demension) {
		if (id == 0) dtlz1(demension);
		if (id == 1) dtlz2(demension);
		if (id == 2) dtlz3(demension);
	}
	inline void dtlz1(int demension) {
		f[0] = v[0];
		double g = 0.0;
		for (int i = 1; i < D; ++i) g += v[i];
		g /= D - 1; g = 9.0 * g + 1;
		f[1] = g * (1 - sqrt(v[0] / g));
	}
	inline void dtlz2(int demension) {
		f[0] = v[0];
		double g = 0.0;
		for (int i = 1; i < D; ++i) g += v[i];
		g /= D - 1; g = 9.0 * g + 1;
		f[1] = g * (1 - (v[0] / g) * (v[0] / g));
	}
	inline void dtlz3(int demension) {
		f[0] = v[0];
		double g = 0.0;
		for (int i = 1; i < D; ++i) g += v[i];
		g /= D - 1; g = 9.0 * g + 1;
		f[1] = g * (1 - sqrt(v[0] / g) - v[0] / g * sin(pi * 10 * v[0]));
	}
};

vector <one> P, Q, R;

void popinit() {
	one t;
	for (int i = 0; i < popsize; ++i) {
		t.init(); P.push_back(t);
		t.init(); Q.push_back(t);
	}
	for (int i = 0; i < popsize * 2; ++i) R.push_back(t);
}
inline int better(int a, int b) {
	if (P[a].rank < P[b].rank) return a; else
		if (P[a].rank > P[b].rank) return b; else
			if (dcmp(P[a].d - P[b].d) >= 0) return a; else return b;
}
inline bool isdominated(const one &i, const one &j) {
	if (dcmp(i.f[0] - j.f[0]) <= 0 && dcmp(i.f[1] - j.f[1]) <= 0)
		if (dcmp(i.f[0] - j.f[0]) < 0 || dcmp(i.f[1] - j.f[1]) < 0) return true;
	return false;
}
void generate(int id, int demension) {
	static bool mark[1005]; //popsize
	static int temp[1005];
	memset(mark, false, sizeof(mark));
	int t1 = randint(0, popsize), t2 = randint(0, popsize), t3 = 0;
	while (t3 < popsize / 2) {
		t1 = randint(0, popsize);
		while (mark[t1]) t1 = randint(0, popsize);
		while (t2 == t1 || mark[t2]) t2 = randint(0, popsize);
		t1 = better(t1, t2);
		temp[t3++] = t1; mark[t1] = true;
	}
	for (int i = 0; i < popsize; ++i)
		if (dcmp(randdouble() - 0.9) <= 0) {
			for (int j = 0; j < D; ++j) {
				double u = randdouble(d1, d2), b;
				if (dcmp(u - 0.5) <= 0) b = pow(2.0 * u, 1.0 / 21); else
					b = 1.0 / pow(2.0 * (1.0 - u), 1.0 / 21);
				int x = randint(0, popsize / 2), y = randint(0, popsize / 2);
				while (y == x) y = randint(0, popsize / 2);
				Q[i].v[j] = 0.5 *((1 - b) * P[temp[x]].v[j] + (1 + b) * P[temp[y]].v[j]);

				if (Q[i].v[j] < 0) Q[i].v[j] = d1;
				if (Q[i].v[j] > 1) Q[i].v[j] = d2;

				if (i + 1 < popsize) {
					Q[i + 1].v[j] = 0.5 * ((1 + b) * P[temp[x]].v[j] + (1 - b) * P[temp[y]].v[j]);

					if (Q[i + 1].v[j] < 0) Q[i + 1].v[j] = d1;
					if (Q[i + 1].v[j] > 1) Q[i + 1].v[j] = d2;
				}
			}
			++i;
		}
		else {
			for (int j = 0; j < D; ++j) {
				int x = randint(0, popsize / 2);
				double u = randdouble(d1, d2);
				if (u < 0.5) u = pow(u * 2, 1.0 / 21) - 1; else
					u = 1.0 - pow(2 * (1 - u), 1.0 / 21);
				Q[i].v[j] = P[temp[x]].v[j] + u;

				if (Q[i].v[j] < 0) Q[i].v[j] = d1;
				if (Q[i].v[j] > 1) Q[i].v[j] = d2;
			}
		}
		for (int i = 0; i < popsize; ++i) {
			Q[i].dtlz1(); //这个程序针对计算DTLZ1函数 
		}
		for (int i = 0; i < popsize; ++i) R[i] = P[i];
		for (int i = 0; i < popsize; ++i) R[i + popsize] = Q[i];
}

vector <int> F[1005];
int level;
void toposort() {
	F[0].clear();
	for (int i = popsize * 2 - 1; i >= 0; --i) {
		R[i].sp.clear(); R[i].np = 0;
		for (int j = popsize * 2 - 1; j >= 0; --j) {
			if (i == j) continue;
			if (isdominated(R[i], R[j])) R[i].sp.push_back(j); else
				if (isdominated(R[j], R[i])) R[i].np++;
		}
		if (R[i].np == 0) {
			R[i].rank = 0; F[0].push_back(i);
		}
	}
	int k = 0;
	while (F[k].size()) {
		level = k;
		F[k + 1].clear();
		for (int i = 0; i < F[k].size(); ++i) {
			int a = F[k][i];
			for (int j = 0; j < R[a].sp.size(); ++j) {
				int b = R[a].sp[j];
				R[b].np--;
				if (R[b].np == 0) {
					R[b].rank = k + 1; F[k + 1].push_back(b);
				}
			}
		}
		k++;
	}
}

inline bool cmp1(int i, int j) {
	return dcmp(R[i].f[0] - R[j].f[0]) < 0;
}
inline bool cmp2(int i, int j) {
	return dcmp(R[i].f[1] - R[j].f[1]) < 0;
}
inline bool cmp3(int i, int j) {
	return dcmp(R[i].d - R[j].d) > 0;
}
void calcdis(int id) {
	if (id > level) return;
	int n = F[id].size();
	for (int i = 0; i < n; ++i) R[F[id][i]].d = 0.0;

	sort(F[id].begin(), F[id].end(), cmp1);
	double delta = R[F[id][n - 1]].f[0] - R[F[id][0]].f[0];
	R[F[id][n - 1]].d = R[F[id][0]].d = 100;
	for (int i = 1; i < n - 1; ++i) {
		int j = F[id][i], left = F[id][i - 1], right = F[id][i + 1];
		R[j].d += (R[right].f[0] - R[left].f[0]) / delta;
	}

	sort(F[id].begin(), F[id].end(), cmp2);
	R[F[id][n - 1]].d = R[F[id][0]].d += 100;
	delta = R[F[id][n - 1]].f[1] - R[F[id][0]].f[1];
	for (int i = 1; i < n - 1; ++i) {
		int j = F[id][i], left = F[id][i - 1], right = F[id][i + 1];
		R[j].d += (R[right].f[1] - R[left].f[1]) / delta;
	}
}

void select() {
	int cnt = 0;
	for (int i = 0; i <= level; ++i) {
		calcdis(i);
		if (cnt + F[i].size() <= popsize)
			for (int j = 0; j < F[i].size(); ++j) P[cnt++] = R[F[i][j]];
		else {
			sort(F[i].begin(), F[i].end(), cmp3);
			for (int j = 0; cnt < popsize && j < F[i].size(); ++j) P[cnt++] = R[F[i][j]];
		}
		if (cnt == popsize) break;
	}
}
struct point {
	double x, y;
	point(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {}
};
inline bool operator < (const point &i, const point &j) {
	return i.x < j.x;
}
void work(int id ,int demension) {
	//store.clear();
	freopen("output.txt", "w", stdout);
	srand(time(0));
	popinit();
	for (int iter = 0; iter < iteration; ++iter) {
		generate(int id, int demension);
		toposort();
		select();
	//	vector<TIndividual> kk;
		for (int i = 0; i < popsize; i++) {
			for (int j = 0; j < demension; j++)
				v2[iter][i][j] = P[i].f[j];
		}
		//store.push_back(kk);
	}
	static vector <point> result;
	result.clear();
	for (int i = 0; i < F[0].size(); ++i) result.push_back(point(R[F[0][i]].f[0], R[F[0][i]].f[1]));
	sort(result.begin(), result.end());
	for (int i = 0; i < F[0].size(); ++i) printf("%.8lf %.8lf\n", result[i].x, result[i].y);
	int j = F[0].size() - 1; j = F[0][j];
	for (int i = 0; i < D; ++i) printf("x[%d]=%.6lf\n", i, R[j].v[i]);
}
/*int main() {
	
	work();
	return 0;
}*/
