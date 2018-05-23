#pragma once
#include <vector>
using namespace std;
class PSO
{
public:

	vector<double> getResult();
	void run(int _id, int _it,bool running);
	vector<double> ans;
	void Clear_ans();
	PSO();
	~PSO();
};

