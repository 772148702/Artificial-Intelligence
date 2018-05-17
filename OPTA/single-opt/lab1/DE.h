#pragma once
#include <vector>
using namespace std;
class DE
{
public:
	
	DE();
	~DE();
	vector<double> ans;
	void run(int _id, int _it);
	vector<double> getResult();
};

