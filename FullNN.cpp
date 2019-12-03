#include "stdafx.h"
#include <iostream>
#include "FNN.h"
//extern  double fRand(double fMin, double fMax);


string file_test = "Test.txt";

//int main()
//{
//	Sample sample;
//	Sample answer;
//	LoadClosePrices(file_test,sample,10);
//	CreateMeanAnswers(sample,answer,3);
//	FNN fnn{};
//	fnn.AddInputLayer(1);
//	fnn.AddFullLayer(20,Tanh);
//	fnn.AddFullLayer(23,Tanh);
//	fnn.AddOutLayer(1,Tanh);
//
//	vector<vector<double>> inp;
//	vector<vector<double>> out;
//	CreateSinSamples(inp, out,1000);
//
//	vector<vector<double>> inp_t;
//	vector<vector<double>> out_t;
//	CreateSinSamples(inp_t, out_t, 1000);
//
//	fnn.Test(inp_t,out_t);
//	clock_t begin = clock();
//	fnn.Learn(inp,out,100,0.01,0.9);
//	clock_t end = clock();
//	fnn.Test(inp_t, out_t);
//	auto time = end - begin;
//	cout << "TIME: " << time << endl;
//}

