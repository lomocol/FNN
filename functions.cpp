#include "stdafx.h"
#include "functions.h"



double functions::fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}
int functions::iRand(int fMin, int fMax)
{
	int f = rand() % (fMax-fMin) + fMin;
	return f;
}

string functions::convertToString(char* a, int size)
{
	int i;
	string s = "";
	for (i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}

void functions::CreateSinSamples(vector<vector<double>>& inp_vec, vector<vector<double>>& out_vec, int size)
{
	double max = 3.14;
	double min = -3.14;
	inp_vec.resize(size);
	out_vec.resize(size);
	for (int i = 0; i < size; i++)
	{
		double x = fRand(min, max);
		inp_vec[i].push_back(x);
		out_vec[i].push_back(sin(x));
	}
}

double functions::Tanh(double x)
{
	return tanh(x);
}

double functions::Sigm(double sum)
{
	return 1 / (1 + pow(e, -sum));
}



double functions::Mean(Sample & inp)
{
	double mean = 0;
	int inp_size = inp.size();
	int lot_size = inp[0].size();
	for (int i = 0; i < inp_size; i++)
	{
		for (int j = 0; j < lot_size; j++)
		{
			mean += inp[i][j];
		}
	}
	mean /= inp_size * lot_size;
	return mean;
}
double functions::Max(Sample & inp)
{
	double max = inp[0][0];

	int inp_size = inp.size();
	int lot_size = inp[0].size();
	for (int i = 0; i < inp_size; i++)
	{
		for (int j = 0; j < lot_size; j++)
		{
			if (max < inp[i][j])
				max = inp[i][j];
		}
	}
	return max;
}
double functions::Max(double * inp,int size)
{
	double max = inp[0];

	for (int i = 0; i < size; i++)
	{
		if (max < inp[i])
			max = inp[i];
	}
	return max;
}

double functions::Min(double * inp, int size)
{
	double min = inp[0];

	for (int i = 0; i < size; i++)
	{
		if (min > inp[i])
			min = inp[i];
	}
	return min;
}

double functions::Min(Sample & inp)
{
	double min = inp[0][0];

	int inp_size = inp.size();
	int lot_size = inp[0].size();
	for (int i = 0; i < inp_size; i++)
	{
		for (int j = 0; j < lot_size; j++)
		{
			if (min > inp[i][j])
				min = inp[i][j];
		}
	}
	return min;
}

double functions::Std(Sample & inp)
{
	double std = 0;
	double mean = Mean(inp);
	int inp_size = inp.size();
	int lot_size = inp[0].size();
	for (int i = 0; i < inp_size; i++)
	{
		for (int j = 0; j < lot_size; j++)
		{
			std += pow(inp[i][j] - mean, 2);
		}
	}
	std /= inp_size * lot_size - 1;
	std = sqrt(std);
	return std;
}


vector<double> functions::Normalize(Sample & inp, double * arr[])
{
	double NewMin = -1;
	double NewMax = 1;
	double mean = Mean(inp);
	double OldMax = Max(inp);
	double OldMin = Min(inp);
	double std = Std(inp);

	int sample_size = inp.size();
	int inp_size = inp[0].size();

	double OldRange = (OldMax - OldMin);
	double	NewRange = (NewMax - NewMin);

	for (int i = 0; i < sample_size; i++)
	{
		for (int j = 0; j < inp_size; j++)
		{
			//inp[i][j] = (inp[i][j] - inp_min) / (inp_max - inp_min);
			inp[i][j] = (((inp[i][j] - OldMin) * NewRange) / OldRange) + NewMin;
			//inp[i].values[j]-=mean;
			//inp[i].values[j]/=std;
		}
	}

	vector<double> resp(3);
	resp[0] = OldMax;
	resp[1] = OldMin;
	resp[2] = mean;
	return resp;
}

double functions::Recover(double NewVal, double OldMin, double OldMax)
{

	

	return 0.0;
}




int functions::StringCount(string file_name)
{
	ifstream file(file_name);
	int sTotal = 0;

	sTotal = count(std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>(), '\n');

	file.close();
	return sTotal;
}



void functions::split3(const std::string& str, vector<string> & cont,char delim)
{
	cont.clear();
	std::size_t current, previous = 0;
	current = str.find(delim);
	while (current != std::string::npos) {
		cont.push_back(str.substr(previous, current - previous));
		previous = current + 1;
		current = str.find(delim, previous);
	}
	cont.push_back(str.substr(previous, current - previous));
}

int functions::LoadClosePrices(string file_name, Sample & inp, int sample_size)
{
	inp.clear();
	int count = 0;
	string str;
	vector<string> result;
	if (file_name.size() == 0)
		return 3;
	ifstream file(file_name);
	if (!file.is_open())
	{
		cout << "FILE not found" << endl;
		return 1;
	}
		
	int str_count = StringCount(file_name);
	count = str_count / sample_size;
	inp.resize( count);
	cout << "STR_COUNT: " <<  str_count << endl;

	for (int i = 0; i < 1; i++)
	{
		getline(file,str);
	}
	for (int i = 0; i < count; i++)
	{
		inp[i].resize(sample_size);
		for (int j = 0; j < sample_size; j++)
		{
			getline(file, str);
			//StringSplit(str, separator, result); //7
			split3(str, result, separator);
			inp[i][j] = stod(result[7]);
		}
	}
	file.close();
	return 0;
}

void functions::LoadClosePrices(string file_name, vector<double>& inp)
{
	inp.clear();
	string str;
	vector<string> result;
	
	ifstream file(file_name);
	if (!file.is_open())
	{
		cout << "FILE not found" << endl;
	}

	int str_count = StringCount(file_name);
	inp.resize(str_count);
	cout << "STR_COUNT: " << str_count << endl;

	for (int i = 0; i < 1; i++)
	{
		getline(file, str);
	}
	for (int i = 0; i < str_count-1; i++)
	{
			getline(file, str);
			split3(str, result, separator);
			inp[i] = stod(result[7]);
	}
	file.close();
}



int functions::CreateMeanAnswers(Sample & inp, Sample & answ, int answ_size)
{
	answ.clear();
	if (inp.size() == 0)
		return 1;
	int inp_size = inp[0].size();
	int sample_size = inp.size();
	double mean = 0;
	answ.resize(sample_size-1);
	for (int i = 1; i < sample_size; i++)
	{
		mean = 0;
		for (int j = 0; j < answ_size; j++)
		{
			mean += inp[i][j];
		}
		mean /= answ_size;
		answ[i - 1].resize(1);
		answ[i - 1][0] = mean;
	}
	inp.pop_back();
	if (answ.size() == 0)
		return 3;
	return 0;
}
