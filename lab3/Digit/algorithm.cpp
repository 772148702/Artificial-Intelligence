#include "stdafx.h"
#include "algorithm.h"


algorithm::algorithm()
{
}


algorithm::~algorithm()
{
}

void algorithm::init1(vector<int> a) {
	new_cur.st = a;
	new_cur.gn = 0;
	new_cur.upDateHn1();
	new_cur.init();  //找到0节点。
	new_cur.fn = new_cur.gn + new_cur.hn;
	while (!open.empty()) open.pop();
	open.push(new_cur);
	while (!record.empty()) record.pop();

}
void algorithm::init2(vector<int> a) {
	new_cur.st = a;
	new_cur.gn = 0;
	new_cur.upDateHn2();
	new_cur.init();  //找到0节点。
	new_cur.fn = new_cur.gn + new_cur.hn;
	while (!open.empty()) open.pop();
	open.push(new_cur);
	while (!record.empty()) record.pop();

}
int factory[] = { 1, 1, 2, 6, 24, 120, 720, 5040, 40320 };
int Cantor(vector<int> r)
{
	int counted = 0;
	int ans = 0;
	for (int i = 0; i < 9; i++) {
		counted = 0;
		for (int j = i + 1; j < 9; j++) {
			if (r[i] > r[j]) counted++;
		}
		ans += counted*factory[8 - i];
	}
	return ans;
}
vector<int> deCantor(int val) {

	vector<int> ans;
	set<int> vis;
	for (int i = 8; i >= 0; i--) {
		int f = val / factory[i];
		val = val%factory[i];
		int k = 0, j = -1;
		for (; j < f; k++) {
			if (vis.count(k) == 0) {
				j++;
			}
			if (j == f) break;
		}
		ans.push_back(k);
		vis.insert(k);
	}
	return ans;
}

//stat 为初始的状态 
bool algorithm::run1() {  //以update1来计算法
	vector<int> cantor(370000, 0);
	
	int  cntCantor = 0;
	while (!open.empty()) {
		state cur = open.top();
		open.pop();
		new_cur = cur;
		int curCantor = Cantor(new_cur.st);
		cantor[curCantor] = 1;
		cntCantor++;
		close.push_back(cur);
		//Record是一个用于帮助界面显示的变量
		Record re(cur, open.size(), cntCantor);
		record.push(re);
		

		if (cur.hn == 0) {
			method.push(cur);
			state  tmp = close[cur.pre];
			while (tmp.pre!=-1) {
				method.push(tmp);
				tmp = close[tmp.pre];
			}
			return true;

		}
		if (cur.r > 0) {
			state tmp1 = cur;
			//计算要交换的来两个数的位置
			int lo1 = cur.r * 3 + cur.c;
			int lo2 = (cur.r - 1) * 3 + cur.c;
			tmp1.r = cur.r - 1;
			tmp1.c = cur.c;
			tmp1.st = cur.st;
			swap(tmp1.st[lo1], tmp1.st[lo2]);

			tmp1.gn = cur.gn + 1;
			tmp1.upDateHn1();
			tmp1.fn = tmp1.hn + tmp1.gn;
			int curCantor = Cantor(tmp1.st);
			if (cantor[curCantor]==0) {
				cntCantor++;
				tmp1.pre = close.size()-1;
				open.push(tmp1);
			}
		
		}
		//向下一行移动
		if (cur.r < 2) {
			state tmp2 = cur;
			int lo1 = cur.r * 3 + cur.c;
			int lo2 = (cur.r + 1) * 3 + cur.c;
			tmp2.r = cur.r + 1;
			tmp2.c = cur.c;
			tmp2.st = cur.st;
			swap(tmp2.st[lo1], tmp2.st[lo2]);

			tmp2.gn = cur.gn + 1;
			tmp2.upDateHn1();
			tmp2.fn = tmp2.hn + tmp2.gn;
			int curCantor = Cantor(tmp2.st);
			if (cantor[curCantor] == 0) {
				cntCantor++;
				tmp2.pre = close.size() - 1;
				open.push(tmp2);
			}
		
		}
		if (cur.c > 0) {
			state tmp3 = cur;
			int lo1 = cur.r * 3 + cur.c;
			int lo2 = (cur.r) * 3 + cur.c - 1;
			tmp3.r = cur.r;
			tmp3.c = cur.c - 1;
			tmp3.st = cur.st;
			swap(tmp3.st[lo1], tmp3.st[lo2]);

			tmp3.gn = cur.gn + 1;
			tmp3.upDateHn1();
			tmp3.fn = tmp3.hn + tmp3.gn;
			int curCantor = Cantor(tmp3.st);
			if (cantor[curCantor] == 0) {
				cntCantor++;
				tmp3.pre = close.size() - 1;
				open.push(tmp3);
			}
		
		}
		if (cur.c < 2) {
			state tmp4 = cur;
			int lo1 = cur.r * 3 + cur.c;
			int lo2 = (cur.r) * 3 + cur.c + 1;
			tmp4.r = cur.r;
			tmp4.c = cur.c + 1;
			tmp4.st = cur.st;
			swap(tmp4.st[lo1], tmp4.st[lo2]);
			tmp4.gn = cur.gn + 1;
			tmp4.upDateHn1();
			tmp4.fn = tmp4.hn + tmp4.gn;
			int curCantor = Cantor(tmp4.st);
			if (cantor[curCantor] == 0) {
				cntCantor++;
				tmp4.pre = close.size() - 1;
				open.push(tmp4);
			}
		
		}
	}
	return false;
}


bool algorithm::run2() {  //以update1来计算法

	vector<int> cantor(370000, 0);
	int  cntCantor = 0;
	while (!open.empty()) {
		state cur = open.top();
		open.pop();
		new_cur = cur;
		int curCantor = Cantor(new_cur.st);
		cantor[curCantor] = 1;
		cntCantor++;
		close.push_back(cur);
		//Record是一个用于帮助界面显示的变量
		Record re(cur, open.size(), cntCantor);
		record.push(re);

		if (cur.hn == 0) {
			method.push(cur);
			state  tmp = close[cur.pre];
			while (tmp.pre != -1) {
				method.push(tmp);
				tmp = close[tmp.pre];
			}
			return true;
		}
		if (cur.r > 0) {
			state tmp1 = cur;
			//计算要交换的来两个数的位置
			int lo1 = cur.r * 3 + cur.c;
			int lo2 = (cur.r - 1) * 3 + cur.c;
			tmp1.r = cur.r - 1;
			tmp1.c = cur.c;
			tmp1.st = cur.st;
			swap(tmp1.st[lo1], tmp1.st[lo2]);

			tmp1.gn = cur.gn + 1;
			tmp1.upDateHn2();
			tmp1.fn = tmp1.hn + tmp1.gn;

			curCantor = Cantor(tmp1.st);
			if (cantor[curCantor] == 0) {
				tmp1.pre = close.size()-1;
				open.push(tmp1);
			}
		
		}
		//向下一行移动
		if (cur.r < 2) {
			state tmp2 = cur;
			int lo1 = cur.r * 3 + cur.c;
			int lo2 = (cur.r + 1) * 3 + cur.c;
			tmp2.r = cur.r + 1;
			tmp2.c = cur.c;
			tmp2.st = cur.st;
			swap(tmp2.st[lo1], tmp2.st[lo2]);

			tmp2.gn = cur.gn + 1;
			tmp2.upDateHn2();
			tmp2.fn = tmp2.hn + tmp2.gn;
			curCantor = Cantor(tmp2.st);
			if (cantor[curCantor] == 0) {
				tmp2.pre = close.size() - 1;
				open.push(tmp2);
			}
		
		}
		if (cur.c > 0) {
			state tmp3 = cur;
			int lo1 = cur.r * 3 + cur.c;
			int lo2 = (cur.r) * 3 + cur.c - 1;
			tmp3.r = cur.r;
			tmp3.c = cur.c - 1;
			tmp3.st = cur.st;
			swap(tmp3.st[lo1], tmp3.st[lo2]);

			tmp3.gn = cur.gn + 1;
			tmp3.upDateHn2();
			tmp3.fn = tmp3.hn + tmp3.gn;
			curCantor = Cantor(tmp3.st);
			if (cantor[curCantor] == 0) {
				tmp3.pre = close.size() - 1;
				open.push(tmp3);
			}
		
		}
		if (cur.c < 2) {
			state tmp4 = cur;
			int lo1 = cur.r * 3 + cur.c;
			int lo2 = (cur.r) * 3 + cur.c + 1;
			tmp4.r = cur.r;
			tmp4.c = cur.c + 1;
			tmp4.st = cur.st;
			swap(tmp4.st[lo1], tmp4.st[lo2]);
			tmp4.gn = cur.gn + 1;
			tmp4.upDateHn2();
			tmp4.fn = tmp4.hn + tmp4.gn;
			curCantor = Cantor(tmp4.st);
			if (cantor[curCantor] == 0) {
				tmp4.pre = close.size() - 1;
				open.push(tmp4);
			}
		
		}
	}
	return false;
}