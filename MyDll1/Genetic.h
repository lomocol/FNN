#pragma once
#include "FNN.h"
#include <map>
typedef multimap<double,vector<double>>  population;
class Genetic
{
public:
	Genetic(int batch_size, int epoch, bool mutation = true,bool multithread = true);
	~Genetic();
	vector<double> OptimizeParametrs();
	void CreatePop();
	void Test();
	static void Learn(int start, int stop);
	vector<double> pRandom();
	vector<FNN*> networks;
private:
	int batch_size;
	int epoch;
	int parametrs_count;
	bool mutation;
	bool multithread;
	population pops;
	
};

