#include "stdafx.h"
#include "Genetic.h"

Genetic::Genetic(int batch_size, int epoch, bool mutation, bool multithread) :batch_size(batch_size),
epoch(epoch), mutation(mutation), multithread(multithread)
{
	parametrs_count = 6;
}

Genetic::~Genetic()
{

}

vector<double> Genetic::OptimizeParametrs()
{
	CreatePop();
	Fnn
	for (int i = 0; i < epoch; i++)
	{
		Test();
	}

	return vector<double>();
}
void Genetic::Test()
{
	thread th1(Learn,0,batch_size/4);	th1.join();

	thread th2(Learn, batch_size / 4, batch_size / 2); th2.join();
	thread th3(Learn, batch_size / 2, batch_size - batch_size / 4);	th3.join();
	thread th4(Learn, batch_size - batch_size / 4, batch_size);	th4.join();
	


}
void Genetic::Learn(int start,int stop)
{
	FNN fnn();
	for (int i = start; i < stop; i++)
	{
		
	}
	cout << endl;
}
void Genetic::CreatePop()
{

	for (int i = 0; i < batch_size; i++)
	{
		pair<double, vector<double>>p(1, pRandom());
		pops.insert(p);
	}

}

vector<double> Genetic::pRandom()
{
	vector<double> param(parametrs_count);

	param[0] = iRand(5, 100);
	param[1] = iRand(1, 30);
	param[2] = iRand(1, 100);
	param[3] = iRand(1, 100);
	param[4] = fRand(0, 1);
	param[5] = fRand(0, 1);

	return param;
}
