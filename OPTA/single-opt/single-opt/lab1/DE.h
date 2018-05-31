#pragma once
#include <vector>
using namespace std;
class DE
{
public:
	
	DE();
	~DE();
	vector<double> ans;
	void run(int _id, int _it,bool running);
	vector<double> getResult();
	void Clear_ans();
};

