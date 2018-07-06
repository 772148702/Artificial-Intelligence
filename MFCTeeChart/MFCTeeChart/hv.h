#pragma once
#include <set>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

inline int cdcmp(double x) {
	if (x > 1e-8) return 1;
	if (x < -1e-8) return -1;
	return 0;
}
struct point2D {
	double x, y;
	point2D(double _x = 0.0, double _y = 0.0) : x(_x), y(_y) {};
};
bool operator < (const point2D &i, const point2D &j) {
	return i.x < j.x;
}
struct point3D {
	double x, y, z;
	point3D(double _x = 0.0, double _y = 0.0, double _z = 0.0) : x(_x), y(_y), z(_z) {};
	bool operator < (const point3D &t) const {
		if (cdcmp(z - t.z) != 0) return cdcmp(z - t.z) > 0;
		if (cdcmp(x - t.z) != 0) return cdcmp(x - t.x) < 0;
		return cdcmp(y - t.y) < 0;
	}
};
double get_hv(vector<double> &x, vector<double> &y) {
	int n = x.size();
	vector <point2D> p; p.clear();
	for (int i = 0; i < n; ++i) p.push_back(point2D(x[i], y[i]));
	sort(p.begin(), p.end());

	double m = x[0], lasty = x[0], ret = 0.0;
	for (int i = 0; i < n; i++) {
		m = max(m, x[i]);
		m = max(m, y[i]);
	}
	m = m + 1;
	lasty = m;
	for (int i = 0; i < n; ++i) {
		ret += (lasty - p[i].y) * (m - p[i].x);
		lasty = p[i].y;
	}
	return ret;
}
double get_hv(vector<double> &x, vector<double> &y, vector<double> &z) {
	int n = x.size();
	vector <point3D> p; p.clear();
	double m = 10000;
	m = x[0];
	for (int i = 0; i < n; i++) {
		m = max(max(x[i], y[i]),m);
		m = max(m, z[i]);
	}
	m = m + 1;
	for (int i = 0; i < n; ++i)
		p.push_back(point3D(m - x[i], m - y[i], m - z[i]));
	double INF = m+1;
	set <point2D> s;
	set <point2D> ::iterator it1, it2, it3, tmp;
	s.clear();
	s.insert(point2D(INF, 0)); s.insert(point2D(0, INF));
	sort(p.begin(), p.end());
	double area = 0.0, ret = 0.0;
	for (int i = 0; i < n;) {
		if (i && cdcmp(p[i].z - p[i - 1].z) != 0) ret += area * (p[i - 1].z - p[i].z);
		int j = i;
		while (j < n && cdcmp(p[j].z - p[i].z) == 0) {
			point2D t = point2D(p[j].x, p[j].z);
			it1 = s.upper_bound(t);
			if (cdcmp(it1->y - p[j].y) >= 0) {
				j++; continue;
			}
			tmp = s.find(t);
			if (tmp != s.end() && cdcmp(tmp->y - p[j].y) >= 0) {
				j++; continue;
			}
			it2 = it1;
			while (true) {
				it3 = it2;
				it3--;
				if (cdcmp(it3->y - p[j].y) >= 0) {
					area += (p[j].x - it3->x) * (p[j].y - it2->y);
					break;
				}
				else {
					area += (p[j].x - it3->x) * (it3->y - it2->y);
					if (cdcmp(it3->y - p[j].y) == 0) {
						it2--;
						break;
					}
				}
				it2--;
			}
			s.erase(it2, it1);
			s.insert(t);
			j++;
		}
		i = j;
	}
	ret += area * p[n - 1].z;
	return ret;
}
