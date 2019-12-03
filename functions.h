#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <string>
#include <cctype>
#include <sstream>
#include  <algorithm>
#include <fstream>
#include <thread>
	using namespace std;
	const double e = 2.71;
	const double pi = 3.1415;
	const char separator = ';';
	typedef vector<vector<double>> Sample;
	namespace functions {
		double fRand(double fMin, double fMax);
		int iRand(int fMin, int fMax);
		void CreateSinSamples(vector<vector<double>> &inp_vec, vector<vector<double>> &out_vec, int size);
		int LoadClosePrices(string file_name, Sample & inp, int sample_size);
		void LoadClosePrices(string name, vector<double> & inp_calc);
		int CreateMeanAnswers(Sample & inp, Sample & answ, int answ_size);
		int StringCount(string file_name);
		string convertToString(char* a, int size);
		void split3(const std::string& str, vector<string> & cont,
			char delim = ' ');
		double Tanh(double x);
		double Sigm(double sum);
		vector<double> Normalize(Sample & inp, double * arr[]);
		double Max(double * inp, int size);
		double Min(double * inp, int size);
		double Recover(double NewVal, double OldMin, double OldMax);
		double Std(Sample & inp);
		double Min(Sample & inp);
		double Max(Sample & inp);
		double Mean(Sample & inp);
	}
