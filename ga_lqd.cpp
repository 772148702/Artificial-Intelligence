#include <bits/stdc++.h>
using namespace std;
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
			for (int i = 0; i < r.size(); ++ i) {
				int j = i + 1;
				if (j == (int)r.size()) j = 0;
				c += dist[r[i]][r[j]];
			}
		}
	};
	double dist[300][300];
	bool vis[300];
	int n;
	vector <double> X, Y;
	vector <int> r1, r2;
	vector <sol> po[2];
	sol ans;
	int pocnt, swapcnt, imax;
	double p1, p2;
	void input(int _n, vector <double> _x, vector <double> _y) {
		X = _x; Y = _y; n = _n;
		for (int i = 0; i < n; ++ i) 
			for (int j = 0; j < n; ++ j) {
				double dx = X[i] - X[j], dy = Y[i] - Y[j];
				dist[i][j] = sqrt(dx * dx + dy * dy);
			}
		pocnt = 100; swapcnt = 10; imax = 2000000;
		p1 = 0.4; p2 = 0.3;
	}
	
	void init() {
		po[0].clear(); ans.c = 1e20;
		sol tmp;
		for (int i = 0; i < pocnt; ++ i) {
			tmp.r.clear();
			for (int j = 0; j < n; ++ j) vis[j] = false;
			for (int j = 0; j < n; ++ j) {
				int t = rand() % n;
				while (vis[t]) t = rand() % n;
				tmp.r.push_back(t); vis[t] = true;
			}
			tmp.calc(dist); po[0].push_back(tmp); if (tmp.c < ans.c) ans = tmp;
		}
	}
	void calcfitness(int id) {
		for (int i = 0; i < pocnt; ++ i) {
			po[id][i].v = (po[id][i].c - ans.c) / ans.c;
			po[id][i].v = 1.0 * (po[id][i].v + 0.5);
		}
	}
	void change(int id) {
		for (int i = 0; i < pocnt; ++ i) {
			double p = 1.0 * rand() / RAND_MAX;
			if (p >= p2) continue;
			for (int j = 0; j < swapcnt; ++ j) {
				int a = rand() % n, b = rand() % n;
				while (a == b) b = rand() % n;
				swap(po[id][i].r[a], po[id][i].r[b]);
			}
			po[id][i].calc(dist);
			if (po[id][i].c < ans.c) ans = po[id][i];
		}
	}
	int select(int id) {
		double p = 1.0 * rand() / RAND_MAX, sum = 0;
		for (int i = 0; i < pocnt; ++ i) sum += po[id][i].v;
		double tmp = 0;
		for (int i = 0; i < pocnt; ++ i) {
			tmp += po[id][i].v / sum;
			if (tmp >= p) return i;
		}
		return pocnt - 1;
	}
	void crossover(int f1, int x, int y) {
		sol tmp;
		int f2 = 1 - f1;
		int mid = rand() % n, w1, w2;
		for (int i = 0; i < n; ++ i) {
			if (po[f1][x].r[i] == mid) w1 = i;
			if (po[f1][y].r[i] == mid) w2 = i;
		}
		
		for (int i = 0; i < n; ++ i) vis[i] = false;
		r1.clear(); r2.clear();
		for (int i = (w1 - 1 + n) % n, j = w2, k = 0; k < n;) {
			i ++; if (i >= n) i -= n;
			int u = po[f1][x].r[i];
			if (!vis[u]) {
				r1.push_back(u); k ++; vis[u] = true;
			}
			j --; if (j < 0) j += n;
			u = po[f1][y].r[j];
			if (!vis[u]) {
				r2.push_back(u); k ++; vis[u] = true;
			}
		}
		tmp.r.clear();
		reverse(r2.begin(), r2.end());
		for (int i = 0; i < r2.size(); ++ i) tmp.r.push_back(r2[i]);
		for (int i = 0; i < r1.size(); ++ i) tmp.r.push_back(r1[i]);
		tmp.calc(dist);
		if (tmp.c < ans.c) ans = tmp;
		po[f2].push_back(tmp);
		
		for (int i = 0; i < n; ++ i) vis[i] = false;
		r1.clear(); r2.clear();
		for (int i = (w1 + 1) % n, j = w2, k = 0; k < n;) {
			i --; if (i < 0) i += n;
			int u = po[f1][x].r[i];
			if (!vis[u]) {
				r1.push_back(u); k ++; vis[u] = true;
			}
			j ++; if (j >= n) j -= n;
			u = po[f1][y].r[j];
			if (!vis[u]) {
				r2.push_back(u); k ++; vis[u] = true;
			}
		}
		tmp.r.clear();
		reverse(r1.begin(), r1.end());
		for (int i = 0; i < r1.size(); ++ i) tmp.r.push_back(r1[i]);
		for (int i = 0; i < r2.size(); ++ i) tmp.r.push_back(r2[i]);
		tmp.calc(dist);
		if (tmp.c < ans.c) ans = tmp;
		po[f2].push_back(tmp);
	}
	void cross(int f1) {
		int f2 = 1 - f1;
		po[f2].clear();
		for (int i = pocnt / 2; i; -- i) {
			int x = select(f1), y = select(f1);
			while (x == y) y = select(f1);
			double p = 1.0 * rand() / RAND_MAX;
			if (p >= p1) {
				po[f2].push_back(po[f1][x]);
				po[f2].push_back(po[f1][y]);
			} else crossover(f1, x, y);
		}
	}
	void showans() {
		/*for (int i = 0; i < n; ++ i) vis[i] = false;
		for (int i = 0; i < n; ++ i) {
			assert(vis[ans.r[i]] == false);
			vis[ans.r[i]] = true;
		}*/
		printf("%lf\n", ans.c);
		for (int i = 0; i < n; ++ i) {
			printf("%d", ans.r[i]);
			if (i + 1 != n) printf("->");
		}
		puts("");
	}
	void work() {
		srand(time(0));
		init();
		int f1 = 0, f2 = 1;
		for (int i = 0; i < imax; ++ i) {
			calcfitness(f1);
			cross(f1);
			change(f2);
			swap(f1, f2);
		}
		showans();
	}
private:
};
GA lqd;
int main() {
	freopen("ch130.tsp", "r", stdin);
	vector <double> x, y;
	x.clear(); y.clear();
	string s;
	for (int i = 0; i < 6; ++ i) getline(cin, s);
	for (int i = 0; i < 130; ++ i) {
		int u;
		double a, b;
		scanf("%d%lf%lf", &u, &a, &b);
		x.push_back(a); y.push_back(b);
	}
	lqd.input(130, x, y);
	lqd.work();
	return 0;
}
