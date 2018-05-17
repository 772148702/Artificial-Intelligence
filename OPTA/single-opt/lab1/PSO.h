#pragma once
#include <vector>
using namespace std;
class PSO
{
public:

	vector<double> getResult();
	void run(int _id, int _it);
	vector<double> ans;
	PSO();
	~PSO();
};

