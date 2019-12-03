// MyDll1.cpp : Defines the exported functions for the DLL application.
//
#include "stdafx.h"
#include "MyDll1.h"



using namespace std;
using namespace functions;

FNN mynet{};

Sample samples;
Sample targets;
Sample samples_t;
Sample targets_t;


_DLLAPI int fibonacci_init(int x)
{
	return -228;
}


_DLLAPI int __stdcall ExportNetworkToFile(char * filename, int name_size)
{
	return mynet.ExportWeights(filename, name_size);
}

_DLLAPI int __stdcall ImportNetworkFromFile(char * filename, int name_size)
{
	return mynet.ImportWeights( filename, name_size);
}

_DLLAPI int __stdcall Normalize()
{
	mynet.Normalize(mynet.inputs, true);
	mynet.Normalize(mynet.inputs_t);
	return 0;
}


_DLLAPI int __stdcall LoadClosePrices(char * c_name, int c_name_size, char * c_name_t, int c_name_size_t, int sample_size)
{
	string name = convertToString(c_name, c_name_size);
	string name_t = convertToString(c_name_t, c_name_size_t);
	int x = 0;
	x += LoadClosePrices(name, mynet.inputs, sample_size);
	x += LoadClosePrices(name_t, mynet.inputs_t, sample_size);
	return x;
}
_DLLAPI int __stdcall LoadVectorOfPrices(char * c_name, int c_name_size)
{
	string name = convertToString(c_name, c_name_size);

	LoadClosePrices(name, mynet.inp_calc);

	return 1;
}

_DLLAPI int __stdcall CreateMeanAnswers(int answer_diaposon)
{
	int x = 0;
	x += CreateMeanAnswers(mynet.inputs, mynet.targets, answer_diaposon);
	x += CreateMeanAnswers(mynet.inputs_t, mynet.targets_t, answer_diaposon);
	return x;
}



_DLLAPI int __stdcall CreateSin(int size, int test_size)
{
	CreateSinSamples(mynet.inputs, mynet.targets, size);
	CreateSinSamples(mynet.inputs_t, mynet.targets_t, test_size);
	return 0;
}

_DLLAPI double __stdcall FeedForward(double * inp, int size)
{
	mynet.FeedForward(mynet.Normalize(inp, size));
	double respond = mynet.Recover(mynet.GetResult());
	return respond;
}

_DLLAPI void __stdcall OldLearn(int epoch, double act_rate, double b,bool trace)
{
	mynet.OldLearn(epoch, act_rate, b,trace);
}
_DLLAPI void __stdcall Learn(int epoch, double act_rate, double b, bool trace)
{
	mynet.Learn(epoch, act_rate, b, trace);
}
_DLLAPI double __stdcall Test()
{
	return mynet.Test();
}
_DLLAPI double __stdcall Check()
{
	double x = mynet.inputs[10][10];
	Normalize();
	double y = mynet.inputs[10][10];
	cout << "x " << x << endl;
	cout << "y " << mynet.Recover(y) << endl;
	return -1;
}

_DLLAPI void __stdcall GeneticAlgoritm(int batch_size, int epoch, bool mutation,bool multi)
{
	Genetic * gn = new Genetic(batch_size,epoch,mutation);
	gn->OptimizeParametrs();
}

_DLLAPI void __stdcall SetFact(int f_num)
{
	
	switch (f_num)
	{
	case 0:
		mynet.SetFact(Tanh);
		break;
	case 1:
		mynet.SetFact(Sigm);
		break;
	default:
		mynet.SetFact(Tanh);
		break;
	}
}

Fact DetectFact(int f_num)
{
	switch (f_num)
	{
	case 0:
		return Tanh;
		break;
	case 1:
		return Sigm;
		break;
	default:
		return Tanh;
		break;
	}
}

_DLLAPI void __stdcall AddInputLayer(int size)
{
	mynet.AddInputLayer(size);
}


_DLLAPI double * __stdcall GetPrices(int & count)
{
	int size = mynet.inp_calc.size();
	double * prices = new double[size];

	for (int i = 0; i < size; i++)
	{
		prices[i] = mynet.inp_calc[i];
	}
	count = size;
	return prices;
}



_DLLAPI void __stdcall AddFullLayer(int size, int f_num)
{
	Fact fact = DetectFact(f_num);
	mynet.AddFullLayer(size, fact);
}


_DLLAPI void __stdcall AddOutLayer(int size, int f_num)
{
	Fact fact = DetectFact(f_num);
	mynet.AddOutLayer(size, fact);
}

int per_time = 0;

_DLLAPI void __stdcall Calculate(double * buffer, int buf_size, double * prices, int prices_size)
{
	int inp_size = mynet.inp_size;
	int out_diaposon = 8;
	double * arr = new double[inp_size];
	for (int i = per_time; i < prices_size; i++)
	{
		for (int j = 0; j < out_diaposon; j++)
		{

		}
	}
}
