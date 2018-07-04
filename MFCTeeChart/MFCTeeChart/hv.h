#pragma once
#include<cstdio>
#include<cstring>
#include<algorithm>
#include <vector>
using namespace std;
const int maxn = 100010;
typedef __int64 lld;
#define max(a,b) a>b?a:b
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
int rm[maxn << 2], mx[maxn << 2], cover[maxn << 2];
int sum[maxn << 2];
struct node {
	int x, y, z;
	bool operator< (const node &cmp) const {
		return z>cmp.z;
	}
}cube[maxn];
void pushup(int rt) {
	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
	rm[rt] = rm[rt << 1 | 1];
	mx[rt] = max(mx[rt << 1], mx[rt << 1 | 1]);
}
void make(int l, int r, int rt, int val) {
	cover[rt] = 1;
	sum[rt] = val*(r - l + 1);
	rm[rt] = mx[rt] = val;
}
void pushdown(int l, int r, int rt) {
	if (cover[rt]) {
		cover[rt] = 0;
		int m = (l + r) >> 1;
		make(lson, mx[rt]);
		make(rson, mx[rt]);
	}
}
void build(int l, int r, int rt) {
	rm[rt] = mx[rt] = sum[rt] = cover[rt] = 0;
	if (l == r) return;
	int m = (l + r) >> 1;
	build(lson);
	build(rson);
}
void update(int L, int R, int val, int l, int r, int rt) {
	if (rm[rt] >= val) return;
	if (L <= l&&r <= R&&mx[rt] <= val) {
		make(l, r, rt, val);
		return;
	}
	pushdown(l, r, rt);
	int m = (l + r) >> 1;
	if (L <= m) update(L, R, val, lson);
	if (R>m) update(L, R, val, rson);
	pushup(rt);
}
double  hhv(vector<double>& x,vector<double>& y ,vector<double>& z) {
	int n, m, i, j;
	n = x.size();
	    m = 3;
		build(0, m - 1, 1);
		for (i = 0; i < n; i++) { 
			cube[i].x = x[i];
			cube[i].y = y[i];
			cube[i].z = z[i];
		}
		sort(cube, cube + n);
		cube[n].z = 0;
		lld vol = 0;
		for (i = 0; i<n; i++) {
			if (cube[i].x>0) update(0, cube[i].x - 1, cube[i].y, 0, m - 1, 1);
			vol += (lld)sum[1] * (cube[i].z - cube[i + 1].z);
		}
		return  m*m*m - vol;
}

