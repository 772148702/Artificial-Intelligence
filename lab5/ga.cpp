#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <cmath>
#include <sstream>
#include <memory.h>

using namespace std;

#define POPSIZE 50               /* population size */
#define MAXGENS 5000            /* max. number of generations */
#define PXOVER 1              /* probability of crossover */
#define PMUTATION 0.15           /* probability of mutation */
#define INF 21000000

class geneIndividual
{
public:
	int index_order[1000];
	int num;
	double fitness;
	double cfitness;

	geneIndividual& operator = (const geneIndividual &g) {
		for (int i = 0; i < 1000; ++ i)
			index_order[i] = g.index_order[i];
		num = g.num;
		fitness = g.fitness;
		cfitness = g.cfitness;
	}
};

struct node
{
	double x;
	double y;
	node(double x, double y) {
		this->x = x;
		this->y = y;
	}
};

geneIndividual generation[POPSIZE+1];
geneIndividual newgeneration[POPSIZE+1];
vector<node> initialCities;
geneIndividual bestIndividual;

/*void initialize(string);
void evaluate(void);
double distance(int, int, const vector<node>);
double total_distance(const int*, int, const vector<node>);
void keep_the_best(void);
void select(void);
void crossover(void);
void mutate(void);
*/

double distance(int index1, int index2, const vector<node> &initialCities) {
	return sqrt((initialCities[index1].x - initialCities[index2].x)*(initialCities[index1].x - initialCities[index2].x)
		+ (initialCities[index1].y - initialCities[index2].y)*(initialCities[index1].y - initialCities[index2].y));
}

double total_distance(const int *index_order, int num, const vector<node> &initialCities) {
	double sum = 0;
	for (int i = 0; i < num - 1; ++ i) {
		sum += distance(index_order[i], index_order[i+1], initialCities);
	}
	sum += distance(index_order[0], index_order[num-1], initialCities);
	return sum;
}

/**********************************/
/* 种群在完成初始化或者交叉变异之后  */
/* 计算适应值以及累计概率以实现轮盘赌*/
/**********************************/
void evaluate() {
	double total_fitness = 0;
	double all_distance = 0;
	for (int i = 0; i < POPSIZE; ++ i) {
		generation[i].fitness = total_distance(generation[i].index_order, generation[i].num, initialCities);
		all_distance += generation[i].fitness;
	}
	for (int i = 0; i < POPSIZE; ++ i) {
		generation[i].fitness = all_distance/generation[i].fitness*10;
		total_fitness += generation[i].fitness;
	}
	double cummulate_fitness = 0;
	for (int i = 0; i < POPSIZE; ++ i) {
		generation[i].cfitness = cummulate_fitness;
		cummulate_fitness += (generation[i].fitness/total_fitness);
	}
}

/*********************************************/
/* 初始化读取TSP文件到initialCities，存储x,y值 */
/* 接着将POPSIZE个种群个体进行随机化的初始化 	 */
/* 并计算适应值和累计概率					     */
/*********************************************/
void initialize(string filename) {
	ifstream infile; 
	infile.open(filename.c_str());
	if(!infile) {
		cout << "error" << endl;
		return;
	}
	string s_line;
	while (getline(infile, s_line)) {
		int space1_index, space2_index;
		for (int i = 0; i < s_line.length(); ++ i) {
			if (s_line[i] == ' ') {
				space1_index = i;
				break;	
			}
		}
		for (int i = s_line.length() - 1; i >= 0; -- i) {
			if (s_line[i] == ' ') {
				space2_index = i;
				break;	
			}
		}
		string s1 = s_line.substr(0, space1_index);
		string s2 = s_line.substr(space1_index + 1, space2_index - space1_index - 1);
		string s3 = s_line.substr(space2_index + 1);
		stringstream ss;
		int index; double x; double y;
		ss << s1;
		ss >> index;
		ss.clear();
		ss << s2;
		ss >> x;
		ss.clear();
		ss << s3;
		ss >> y;
		node temp(x, y);
		initialCities.push_back(temp);
	}
	infile.close();

	//randomly evalue
	for (int i = 0; i < POPSIZE; ++ i) {
		generation[i].num = initialCities.size();
		for (int j = 0; j < generation[i].num; ++ j) {
			generation[i].index_order[j] = j;
		}
		random_shuffle(generation[i].index_order, generation[i].index_order + generation[i].num);
	}
	evaluate();

	//choose the best
	double _max = -INF;
	for (int i = 0; i < POPSIZE; ++ i) {
		if (generation[i].fitness > _max) {
			_max = generation[i].fitness;
			bestIndividual = generation[i];
		}
	}
}

/********************************************/
/* 轮盘赌选择 								*/
/* 选择后计算适应值和累计概率供给下一次选择使用 */
/* 应删去上一行的功能，因为没用 				*/
/********************************************/
void select() {
	//srand(19270816U);
	for (int i = 0; i < POPSIZE; ++ i) {
		double p = double(rand())/RAND_MAX;
		if (p > generation[POPSIZE - 1].cfitness) {
			newgeneration[i] = generation[POPSIZE - 1];
			continue;
		}
		for (int j = 0; j < POPSIZE - 1; ++ j) {
			if (p <= generation[j + 1].cfitness && p > generation[j].cfitness) {
				newgeneration[i] = generation[j];
				break;
			}
		}
	}
	for (int i = 0; i < POPSIZE; ++ i)
		generation[i] = newgeneration[i];
}

bool isthesame(const geneIndividual& g1, const geneIndividual& g2) {
	for (int i = 0; i < initialCities.size(); ++ i) {
		if (g1.index_order[i] != g2.index_order[i])
			return false;
	}
	return true;
}

void PMXcrossover(int gene_index1, int gene_index2, int order_index1, int order_index2) {
	//cout << "PMXcrossover begin" << endl;
	int par1_map[1000];
	int par2_map[1000];
	for (int i = 0; i < 1000; ++ i) {
		par1_map[i] = i;
		par2_map[i] = i;
	}
	//debug imformation
	/*cout << "par1: " << endl;
	for (int i = order_index1; i <= order_index2; ++ i) {
		cout << generation[gene_index1].index_order[i] << ' ';
	}
	cout << endl;
	cout << "par2: " << endl;
	for (int i = order_index1; i <= order_index2; ++ i) {
		cout << generation[gene_index2].index_order[i] << ' ';
	}
	cout << endl;*/
	//debug end

	//exchange
	for (int i = order_index1; i <= order_index2; ++ i) {
		//cout << "previous value: " << generation[gene_index1].index_order[i] << ' ' << generation[gene_index2].index_order[i] << endl;
		swap(generation[gene_index1].index_order[i], generation[gene_index2].index_order[i]);
		//cout << "later value: " << generation[gene_index1].index_order[i] << ' ' << generation[gene_index2].index_order[i] << endl;
		par1_map[generation[gene_index1].index_order[i]] = generation[gene_index2].index_order[i];
		par2_map[generation[gene_index2].index_order[i]] = generation[gene_index1].index_order[i];
	}

	//mapping
	//0 - order_index1 map
	for (int i = 0; i < order_index1; ++ i) {
		//par1
		int current = generation[gene_index1].index_order[i];
		while (par1_map[current] != current) {
			current = par1_map[current];
		}
		generation[gene_index1].index_order[i] = current;
		//par2
		current = generation[gene_index2].index_order[i];
		while (par2_map[current] != current) {
			current = par2_map[current];
		}
		generation[gene_index2].index_order[i] = current;
	}
	//order_index2 + 1 - end map
	for (int i = order_index2 + 1; i < initialCities.size(); ++ i) {
		//par1
		int current = generation[gene_index1].index_order[i];
		while (par1_map[current] != current) {
			current = par1_map[current];
		}
		generation[gene_index1].index_order[i] = current;
		//par2
		current = generation[gene_index2].index_order[i];
		while (par2_map[current] != current) {
			current = par2_map[current];
		}
		generation[gene_index2].index_order[i] = current;
	}
}


/********************************************************/
/* 交叉								        			*/
/* 交叉选用PMX算子，相应算子可以另行改变   					*/
/* 选择领域内最好的交叉出来的结果							*/ 
/*领域大小为8 小了效果不佳 大了速度降低 有可能退化为局部搜索 */
/********************************************************/
void crossover() {
	//cout << "crossover" << endl;
	//srand(19270816U);
	for (int i = 0; i < POPSIZE; ++ i) {
		if (rand() < PXOVER * RAND_MAX) {
			int gene_index1 = rand() % POPSIZE;
			int gene_index2 = rand() % POPSIZE;
			while (gene_index2 == gene_index1)
				gene_index2 = rand() % POPSIZE;
			geneIndividual temp1 = generation[gene_index1];
			geneIndividual temp2 = generation[gene_index2];
			geneIndividual PMX_best1 = generation[gene_index1];
			geneIndividual PMX_best2 = generation[gene_index2];
			double best_distance = total_distance(generation[gene_index1].index_order, generation[gene_index1].num, initialCities)
					+ total_distance(generation[gene_index2].index_order, generation[gene_index2].num, initialCities);
			for (int num = 0; num < 8; ++ num) {
				int order_index1 = rand() % initialCities.size();
				int order_index2 = rand() % initialCities.size();
				while (order_index2 == order_index1)
					order_index2 = rand() % initialCities.size();
				if (order_index1 > order_index2)
					swap(order_index1, order_index2);
				PMXcrossover(gene_index1, gene_index2, order_index1, order_index2);
				double distance_current = total_distance(generation[gene_index1].index_order, generation[gene_index1].num, initialCities)
					+ total_distance(generation[gene_index2].index_order, generation[gene_index2].num, initialCities);
				if (distance_current < best_distance) {
					PMX_best1 = generation[gene_index1];
					PMX_best2 = generation[gene_index2];
					best_distance = distance_current;
				}
				generation[gene_index1] = temp1;
				generation[gene_index2] = temp2;
			}
			generation[gene_index1] = PMX_best1;
			generation[gene_index2] = PMX_best2;
			//debug imformation
			/*if (isthesame(temp1, generation[gene_index1])) {
				c_count ++;
				cout << c_count << " same" << endl;
				cout << "order: " << order_index1 << ' ' << order_index2 << endl;
				cout << "par1: " << gene_index1 << endl;
				for (int i = 0; i < initialCities.size(); ++ i) {
					cout << temp1.index_order[i] << ' ';
				}
				cout << endl;
				cout << "par2: " << gene_index2 << endl;
				for (int i = 0; i < initialCities.size(); ++ i) {
					cout << temp2.index_order[i] << ' ';
				}
				cout << endl;
				cout << "gene1: " << endl;
				for (int i = 0; i < initialCities.size(); ++ i) {
					cout << generation[gene_index1].index_order[i] << ' ';
				}
				cout << endl;
				cout << "gene2: " << endl;
				for (int i = 0; i < initialCities.size(); ++ i) {
					cout << generation[gene_index2].index_order[i] << ' ';
				}
				cout << endl;
			}
			if (isthesame(temp2, generation[gene_index2]))
				cout << 2 << endl;
			*/
		}
	}
	
}

//局部搜索可以做多次选择最好的 有深度的局部搜索
void mutate() {
	//srand(19270816U);
	for (int h = 0; h < POPSIZE; ++ h) {
		if (rand() < PMUTATION * RAND_MAX) {
			geneIndividual best_current = generation[h];
			geneIndividual temp = generation[h];
			double best_distance = total_distance(generation[h].index_order, generation[h].num, initialCities);
			for (int num = 0; num < 5; num ++) {
				int index1 = rand() % initialCities.size();
				int index2 = rand() % initialCities.size();
				while (index2 == index1) {
					index2 = rand() % initialCities.size();
				}
				if (index1 > index2) swap(index1, index2);
				for (int i = index1; i <= (index1 + index2)/2; ++ i)
					swap(generation[h].index_order[i], generation[h].index_order[index2 + index1 - i]);
				double current_distance = total_distance(generation[h].index_order, generation[h].num, initialCities);
				if (current_distance < best_distance) {
					best_distance = current_distance;
					best_current = generation[h];
				}
				generation[h] = temp;
			}
			generation[h] = best_current;		
		}
	}
}

bool isvalid(string s) {
	bool isvisited[1000] = {0};
	for (int i = 0; i < POPSIZE; ++ i) {
		for (int j = 0; j < initialCities.size(); ++ j) {
			if (isvisited[generation[i].index_order[j]]) {
				cout << s << endl;
				cout << "invalid in generationIndividual : " << i << " index " << j << endl;
				for (int h = 0; h < initialCities.size(); ++ h)
					cout << generation[i].index_order[h] << ' ';
				cout << endl;
				return false;  
			}
			else {
				isvisited[generation[i].index_order[j]] = 1;
			}
		}
		memset(isvisited, 0, sizeof(isvisited));
	}
	return true;
}

void find_and_report_best() {
	double _max = -INF;
	for (int i = 0; i < POPSIZE; ++ i) {
		if (generation[i].fitness > _max) {
			_max = generation[i].fitness;
			generation[POPSIZE] = generation[i];
		}
	}
	double current_best = total_distance(generation[POPSIZE].index_order, initialCities.size(), initialCities);
	double all_best = total_distance(bestIndividual.index_order, initialCities.size(), initialCities);
	if (current_best < all_best) {
		bestIndividual = generation[POPSIZE];
		cout << "current best" << current_best << endl;
	}
	cout << current_best << endl;
}

void keep_the_best() {
	generation[0] = bestIndividual;
}

void print_all() {
	for (int i = 0; i < POPSIZE; ++ i) {
		for (int j = 0; j < initialCities.size(); ++ j)
			cout << generation[i].index_order[j] << ' ';
		cout << endl;
	}
}

int main() {
	initialize("ch130.tsp");
	srand(19270816U);
	//print_all();
	int n_gene = MAXGENS;
	while (n_gene --) {
		select();
		keep_the_best();
		crossover();
		mutate();
		evaluate();
		find_and_report_best();
		//cout << total_distance(bestIndividual.index_order, initialCities.size(), initialCities) << endl;
	}
	cout << "test best " << total_distance(bestIndividual.index_order, bestIndividual.num, initialCities);
	cout << endl;
	cout <<  (total_distance(bestIndividual.index_order, bestIndividual.num, initialCities) - 6110)/6110 << endl;
	cout << "final order: " << endl;
	for (int i = 0; i < initialCities.size(); ++ i)
		cout << bestIndividual.index_order[i] << ' ';
	cout << endl;
	return 0;
}
