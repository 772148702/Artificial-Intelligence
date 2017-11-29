#pragma once
#include <vector>
#include<algorithm>
using namespace std;
class ga_lqd
{
public:
	ga_lqd();
	~ga_lqd();
};

class GA {
public:
	struct sol {
		vector <int> r;
		double c, v;
		void clear() {
			r.clear(); c = v = 0.0;
		}
		void calc(double dist[][300]) {
			c = 0.0;
			for (int i = 0; i < r.size(); ++i) {
				int j = i + 1;
				if (j == (int)r.size()) j = 0;
				c += dist[r[i]][r[j]];
			}
		}
	};
	double dist[300][300];
	bool vis[300];
    int num;
	vector <double> X, Y;
	vector <int> r1, r2;
	vector <sol> po[2];
	sol ans;
	int pocnt, swapcnt, badimax;
	double p1, p2;
	void input(int k, vector <double> _x, vector <double> _y) {
		num = k;
		X.clear();
		Y.clear();
		for (int i = 1; i <= num; i++) {
			X.push_back(_x[i]);
			Y.push_back(_y[i]);
		}
		//X = _x; Y = _y; 
		for (int i = 0; i <num; ++i)
			for (int j = 0; j <num; ++j) {
				double dx = X[i] - X[j], dy = Y[i] - Y[j];
				dist[i][j] = sqrt(dx * dx + dy * dy);
			}
		pocnt = 60; swapcnt = 7; badimax = 50000;
		p1 = 0.8; p2 = 0.4;
	}
	vector<int> getAns() {
		vector<int> tmp = ans.r;
		for (auto  ss:tmp) {
			ss++;
		}
		return tmp;
	}
	void init() {
		po[0].clear(); ans.c = 1e20;
		sol tmp;
		for (int i = 0; i < pocnt; ++i) {
			tmp.r.clear();
			for (int j = 0; j < num; ++j) vis[j] = false;
			for (int j = 0; j < num; ++j) {
				int t = rand() % num;
				while (vis[t]) t = rand() % num;
				tmp.r.push_back(t); vis[t] = true;
			}
			tmp.calc(dist); po[0].push_back(tmp); if (tmp.c < ans.c) ans = tmp;
		}
	}
	void calcfitness(int id) {
		for (int i = 0; i < pocnt; ++i) {
			po[id][i].v = (po[id][i].c - ans.c) / ans.c;
			po[id][i].v = 1.0 * (po[id][i].v + 0.5);
		}
	}
	void change(int id) {
		for (int i = 0; i < pocnt; ++i) {
			double p = 1.0 * rand() / RAND_MAX;
			if (p >= p2) continue;
			for (int j = 0; j < swapcnt; ++j) {
				int a = rand() % num, b = rand() % num;
				while (a == b) b = rand() % num;
				if (a > b) swap(a, b);
				reverse(po[id][i].r.begin() + a, po[id][i].r.begin() + b + 1);
				//swap(po[id][i].r[a], po[id][i].r[b]);
			}
			po[id][i].calc(dist);
			if (po[id][i].c < ans.c) ans = po[id][i];
		}
	}
	int select(int id) {
		double p = 1.0 * rand() / RAND_MAX, sum = 0;
		for (int i = 0; i < pocnt; ++i) sum += po[id][i].v;
		double tmp = 0;
		for (int i = 0; i < pocnt; ++i) {
			tmp += po[id][i].v / sum;
			if (tmp >= p) return i;
		}
		return pocnt - 1;
	}
	void crossover(int f1, int x, int y) {
		sol tmp;
		int f2 = 1 - f1;
		int mid = rand() % num, w1, w2;
		for (int i = 0; i < num; ++i) {
			if (po[f1][x].r[i] == mid) w1 = i;
			if (po[f1][y].r[i] == mid) w2 = i;
		}

		for (int i = 0; i < num; ++i) vis[i] = false;
		r1.clear(); r2.clear();
		for (int i = (w1 - 1 + num) % num, j = w2, k = 0; k < num;) {
			i++; if (i >= num) i -= num;
			int u = po[f1][x].r[i];
			if (!vis[u]) {
				r1.push_back(u); k++; vis[u] = true;
			}
			j--; if (j < 0) j += num;
			u = po[f1][y].r[j];
			if (!vis[u]) {
				r2.push_back(u); k++; vis[u] = true;
			}
		}
		tmp.r.clear();
		reverse(r2.begin(), r2.end());
		for (int i = 0; i < r2.size(); ++i) tmp.r.push_back(r2[i]);
		for (int i = 0; i < r1.size(); ++i) tmp.r.push_back(r1[i]);
		tmp.calc(dist);
		if (tmp.c < ans.c) ans = tmp;
		po[f2].push_back(tmp);

		for (int i = 0; i < num; ++i) vis[i] = false;
		r1.clear(); r2.clear();
		for (int i = (w1 + 1) % num, j = w2, k = 0; k < num;) {
			i--; if (i < 0) i += num;
			int u = po[f1][x].r[i];
			if (!vis[u]) {
				r1.push_back(u); k++; vis[u] = true;
			}
			j++; if (j >= num) j -= num;
			u = po[f1][y].r[j];
			if (!vis[u]) {
				r2.push_back(u); k++; vis[u] = true;
			}
		}
		tmp.r.clear();
		reverse(r1.begin(), r1.end());
		for (int i = 0; i < r1.size(); ++i) tmp.r.push_back(r1[i]);
		for (int i = 0; i < r2.size(); ++i) tmp.r.push_back(r2[i]);
		tmp.calc(dist);
		if (tmp.c < ans.c) ans = tmp;
		po[f2].push_back(tmp);
	}
	void cross(int f1) {
		int f2 = 1 - f1;
		po[f2].clear();
		for (int i = pocnt / 2; i; --i) {
			int x = select(f1), y = select(f1);
			while (x == y) y = select(f1);
			double p = 1.0 * rand() / RAND_MAX;
			if (p >= p1) {
				po[f2].push_back(po[f1][x]);
				po[f2].push_back(po[f1][y]);
			}
			else crossover(f1, x, y);
		}
	}
	void showans() {
		/*for (int i = 0; i < n; ++ i) vis[i] = false;
		for (int i = 0; i < n; ++ i) {
		assert(vis[ans.r[i]] == false);
		vis[ans.r[i]] = true;
		}*/
		printf("%lf\n", ans.c);
		for (int i = 0; i < num; ++i) {
			printf("%d", ans.r[i]);
			if (i + 1 != num) printf("->");
		}
		puts("");
	}
	void work() {
		srand(time(0));
		init();
		int f1 = 0, f2 = 1;
		for (int i = 0; i < badimax;) {
			double last = ans.c;
			calcfitness(f1);
			cross(f1);
			change(f2);
			swap(f1, f2);
			if (ans.c + 1e-4 < last) {
				i = 0;
				printf("%lf\n", ans.c);
			}
			else i++;
		}
		//showans();
	}
private:
};