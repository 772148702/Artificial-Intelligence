#pragma once
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
const int D = 10;
int popsize = 200; //种群大小
bool isNsgaEnd = false;

struct one {
	double v[D];
	vector <int> sp;
	int np, rank;
	double d, f[3];
	void init(int id, int demension) {
		for (int i = 0; i < D; ++i) v[i] = randdouble();
		sp.clear();
		calcf(id, demension); //这个程序针对计算DTLZ1函数 
	}
	inline void calcf(int id, int demension) {
		if (id == 0) {
			if (demension == 3) {
				double g = 0;
				for (int n = 2; n < D; n++)
					g = g + pow(v[n] - 0.5, 2) - cos(20 * pi*(v[n] - 0.5));
				g = 100 * (D - 2 + g);
				f[0] = 0.5*(1 + g)*v[0] * v[1];
				f[1] = 0.5*(1 + g)*v[0] * (1 - v[1]);

				f[2] = 0.5*(1 + g)*(1 - v[0]);
			}
			else {
				double g = 0;
				for (int n = 1; n < D; n++)
					g = g + pow(v[n] - 0.5, 2) - cos(20 * pi*(v[n] - 0.5));
				g = 100 * (D - 1 + g);
				f[0] = 0.5*(1 + g)*v[0];
				f[1] = 0.5*(1 + g)* (1 - v[0]);


			}
		}
		if (id == 1) {
			if (demension == 3) {
				double g = 0;

				for (int n = 2; n < D; n++)
				{
					double x = (v[n] - 0.5);
					g = g + x*x;;
				}
				f[0] = (1 + g)*cos(v[0] * pi / 2)*cos(v[1] * pi / 2);
				f[1] = (1 + g)*cos(v[0] * pi / 2)*sin(v[1] * pi / 2);
				f[2] = (1 + g)*sin(v[0] * pi / 2);
			}
			else {
				double g = 0;

				for (int n = 1; n < D; n++)
				{
					double x = (v[n] - 0.5);
					g = g + x*x;;
				}
				f[0] = (1 + g)*cos(v[0] * pi / 2);
				f[1] = (1 + g)*sin(v[0] * pi / 2);

			}
		}
		if (id == 2) {
			if (demension == 3) {
				double g = 0;
				for (int n = 2; n < D; n++)
					g = g + pow(v[n] - 0.5, 2) - cos(20 * pi*(v[n] - 0.5));
				g = 100 * (D - 2 + g);
				f[0] = (1 + g)*cos(v[0] * pi / 2)*cos(v[1] * pi / 2);
				f[1] = (1 + g)*cos(v[0] * pi / 2)*sin(v[1] * pi / 2);

				f[2] = (1 + g)*sin(v[0] * pi / 2);
			}
			else {
				double g = 0;
				for (int n = 1; n < D; n++)
					g = g + pow(v[n] - 0.5, 2) - cos(20 * pi*(v[n] - 0.5));
				g = 100 * (D - 1 + g);
				f[0] = (1 + g)*cos(v[0] * pi / 2);
				f[1] = (1 + g)*sin(v[0] * pi / 2);


			}
		}
		if (id == 3) {
			if (demension == 3) {
				double g = 0;
				double xx = (v[0] + v[1]) / 2.0;
				for (int n = 2; n < D; n++)
				{
					double x = (v[n] - 0.5);
					g = g + x*x;;
				}
				f[0] = (1 + g)*cos(pow(v[0], pi) * pi / 2)*cos(pow(v[1], pi) * pi / 2);
				f[1] = (1 + g)*cos(pow(v[0], pi) * pi / 2)*sin(pow(v[1], pi) * pi / 2);

				f[2] = (1 + g)*sin(pow(v[0], pi) * pi / 2);
			}
			else {
				double g = 0;
				double xx = (v[0] + v[1]) / 2.0;
				for (int n = 1; n < D; n++)
				{
					double x = (v[n] - 0.5);
					g = g + x*x;;
				}
				f[0] = (1 + g)*cos(pow(v[0], pi) * pi / 2);
				f[1] = (1 + g)*sin(pow(v[0], pi) * pi / 2);

			}
		}
	}
};

vector <one> P, Q, R;

void popinit(int id, int demension) {
	one t;
	for (int i = 0; i < popsize; ++i) {
		t.init(id, demension); P.push_back(t);
		t.init(id, demension); Q.push_back(t);
	}
	for (int i = 0; i < popsize * 2; ++i) R.push_back(t);
}
inline int better(int a, int b) {
	if (P[a].rank < P[b].rank) return a; else
		if (P[a].rank > P[b].rank) return b; else
			if (dcmp(P[a].d - P[b].d) >= 0) return a; else return b;
}
inline bool isdominated(const one &i, const one &j, const int &demension) {
	for (int k = 0; k < demension; ++k)
		if (dcmp(i.f[k] - j.f[k]) > 0) return false;
	for (int k = 0; k < demension; ++k)
		if (dcmp(i.f[k] - j.f[k]) < 0) return true;
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
		for (int i = 0; i < popsize; ++i) Q[i].calcf(id, demension);
		for (int i = 0; i < popsize; ++i) R[i] = P[i];
		for (int i = 0; i < popsize; ++i) R[i + popsize] = Q[i];
}

vector <int> F[1005];
int level;
void toposort(int demension) {
	F[0].clear();
	for (int i = popsize * 2 - 1; i >= 0; --i) {
		R[i].sp.clear(); R[i].np = 0;
		for (int j = popsize * 2 - 1; j >= 0; --j) {
			if (i == j) continue;
			if (isdominated(R[i], R[j], demension)) R[i].sp.push_back(j); else
				if (isdominated(R[j], R[i], demension)) R[i].np++;
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
	return dcmp(R[i].f[2] - R[j].f[2]) < 0;
}
inline bool cmp4(int i, int j) {
	return dcmp(R[i].d - R[j].d) > 0;
}
void calcdis(int id, int demension) {
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

	if (demension == 2) return;
	sort(F[id].begin(), F[id].end(), cmp3);
	R[F[id][n - 1]].d = R[F[id][0]].d += 100;
	delta = R[F[id][n - 1]].f[2] - R[F[id][0]].f[2];
	for (int i = 1; i < n - 1; ++i) {
		int j = F[id][i], left = F[id][i - 1], right = F[id][i + 1];
		R[j].d += (R[right].f[2] - R[left].f[2]) / delta;
	}
}

void select(int demension) {
	int cnt = 0;
	for (int i = 0; i <= level; ++i) {
		calcdis(i, demension);
		if (cnt + F[i].size() <= popsize)
			for (int j = 0; j < F[i].size(); ++j) P[cnt++] = R[F[i][j]];
		else {
			sort(F[i].begin(), F[i].end(), cmp4);
			for (int j = 0; cnt < popsize && j < F[i].size(); ++j) P[cnt++] = R[F[i][j]];
		}
		if (cnt == popsize) break;
	}
}
void work(int id, int demension, int iteration, vector<vector<one>>& vsga) {
	srand(time(0));
	vsga.clear();
	P.clear();
	Q.clear();
	R.clear();
	for (int i = 0; i < 1005; i++) F[i].clear();
	popinit(id, demension);
	for (int iter = 0; iter < iteration; ++iter) {
		if (isNsgaEnd == true) return;
		generate(id, demension);
		toposort(demension);
		select(demension);
		vector<one> tmp;
		int len = F[0].size();
		for (int i = 0; i < len; i++) {
			tmp.push_back(R[F[0][i]]);
		}
		vsga.push_back(tmp);
	}

}
int main() {

	return 0;
}
