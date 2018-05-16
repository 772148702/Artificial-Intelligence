#pragma once
#include <vector>
using namespace std;
class PSO
{
public:

	vector<double> getResult();
	void run(int id);
	vector<double> ans;
	PSO();
	~PSO();
};

