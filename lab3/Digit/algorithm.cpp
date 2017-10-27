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
	open.push(new_cur);

}
void algorithm::init2(vector<int> a) {
	new_cur.st = a;
	new_cur.gn = 0;
	new_cur.upDateHn2();
	new_cur.init();  //找到0节点。
	new_cur.fn = new_cur.gn + new_cur.hn;
	open.push(new_cur);

}



//stat 为初始的状态 
bool algorithm::run1() {  //以update1来计算法
	while (!open.empty()) {
		state cur = open.top();
		open.pop();
		new_cur = cur;
		close.insert(cur);
		Record re(cur, open.size(), close.size());
		record.push(re);
		

		if (cur.hn == 0) {
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
			if (close.count(tmp1) == 0) {
				open.push(tmp1);
			}
			if (tmp1.hn == 0) {
				new_cur = tmp1;
				return true;
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
			if (close.count(tmp2) == 0) {
				open.push(tmp2);
			}
			if (tmp2.hn == 0) {
				new_cur = tmp2;
				return true;
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
			if (close.count(tmp3) == 0) {
				open.push(tmp3);
			}
			if (tmp3.hn == 0) {
				new_cur = tmp3;
				return true;
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
			if (close.count(tmp4) == 0) {
				open.push(tmp4);
			}
			if (tmp4.hn == 0) {
				new_cur = tmp4;
				return true;
			}
		}
	}
	return false;
}


bool algorithm::run2() {  //以update1来计算法
	while (!open.empty()) {
		state cur = open.top();
		open.pop();
		new_cur = cur;
		close.insert(cur);
		Record re(cur, open.size(), close.size());
		record.push(re);


		if (cur.hn == 0) {
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
			if (close.count(tmp1) == 0) {
				open.push(tmp1);
			}
			if (tmp1.hn == 0) {
				new_cur = tmp1;
				return true;
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
			if (close.count(tmp2) == 0) {
				open.push(tmp2);
			}
			if (tmp2.hn == 0) {
				new_cur = tmp2;
				return true;
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
			if (close.count(tmp3) == 0) {
				open.push(tmp3);
			}
			if (tmp3.hn == 0) {
				new_cur = tmp3;
				return true;
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
			if (close.count(tmp4) == 0) {
				open.push(tmp4);
			}
			if (tmp4.hn == 0) {
				new_cur = tmp4;
				return true;
			}
		}
	}
	return false;
}