#include "stdafx.h"
#include "FNN.h"

FNN::FNN()
{
	inp_size = 0;
	out_size = 0;
	layers_count = 0;
}

FNN::~FNN()
{
	for (auto i = layers.begin(); i !=layers.end(); i++)
	{
		delete *i;
	}
}

void FNN::AddInputLayer(int size)
{
	inp_size = size;
	layers.push_back(new iLayer(size));
	layers_count++;
	topology.push_back(size);
}

void FNN::AddFullLayer(int size, Fact f)
{
	layers.push_back(new fLayer(size, layers.back(), f));
	layers_count++;
	topology.push_back(size);
}

void FNN::AddOutLayer(int size, Fact f)
{
	out_size = size;
	layers.push_back(new oLayer(size, layers.back(), f));
	layers_count++;
	topology.push_back(size);
}

double FNN::GetResult()
{
	return layers[layers_count - 1]->values[0];
}

void FNN::BackPropagation(double act_rate)
{
	for (int i = 1; i < layers_count; i++)
	{
		layers[i]->BackPropagation(act_rate);
	}
}

void FNN::SetB(double _b)
{
	for (int i = 1; i < layers_count; i++)
	{
		static_cast<hLayer*>(layers[i])->b = _b;
	}
}

void FNN::FeedForward(vector<double>& inp_vec)
{
	static_cast<iLayer*>(layers[0])->FeedForward(inp_vec);
	for (int i = 1; i < layers_count; i++)
	{
		layers[i]->FeedForward();
	}
}

void FNN::FeedForward(vector<double>&& inp_vec)
{
	static_cast<iLayer*>(layers[0])->FeedForward(inp_vec);
	for (int i = 1; i < layers_count; i++)
	{
		layers[i]->FeedForward();
	}
}

double FNN::FeedForward(double * inp, int size)
{
	static_cast<iLayer*>(layers[0])->FeedForward(inp, size);
	for (int i = 1; i < layers_count; i++)
	{
		layers[i]->FeedForward();
	}
	return layers[layers_count - 1]->values[0];
}

int FNN::ImportWeights(char * filename, int name_size)
{
	const char separator = ' ';
	char  strd[] = "dfd";
	vector<string> topology;
	ifstream file(filename);

	if (!file.is_open())
	{
		cout << "Cannot create file!" << endl;
		return -1;
	}
	string str;
	getline(file, str);

	split3(str, topology, separator);
	topology.resize(topology.size() - 1);
	AddInputLayer(stoi(topology[0]));
	for (int i = 1; i < topology.size()-1; i++)
	{
		AddFullLayer(stoi(topology[i]), Tanh);
	}
	AddOutLayer(stoi(topology.back()),Tanh);
	vector<vector<double>> vWeights;
	for (int l = 1; l < topology.size(); l++)
	{
		vWeights.clear();
		for (int n = 0; n< stoi(topology[l]); n++)
		{
			vWeights.push_back(vector<double>());
			for (int pn = 0; pn < stoi(topology[l-1])+1; pn++)
			{
				getline(file, str);
				vWeights[n].push_back(stod(str));
			}
		}
		static_cast<hLayer*>(layers[l])->SetWeights(vWeights);
		getline(file, str);
	}
	

	file.close();
	return 0;
}

void FNN::GetMistake(vector<double>& answ_vec)
{

	static_cast<oLayer*>(layers[layers_count - 1])->GetMistake(answ_vec);
	for (int i = layers_count - 2; i > 1; i--)
	{
		layers[i]->GetMistake();
	}

}


void FNN::Learn(Sample& inp_vec, Sample& answ_vec, int epoch, double act_rate, double b,bool trace)
{
	SetB(b);
	for (int i = 0; i < epoch; i++)
	{
		for (int j = 0; j < inp_vec.size(); j++)
		{
			FeedForward(inp_vec[j]);
			GetMistake(answ_vec[j]);
			BackPropagation(act_rate);
		}
	}

}

void FNN::OldLearn(Sample & inp_vec, Sample & answ_vec, int epoch, double act_rate, double b, bool trace)
{
	SetB(b);
	for (int i = 0; i < epoch; i++)
	{
		for (int j = 0; j < inp_vec.size(); j++)
		{
			FeedForward(inp_vec[j]);
			GetMistake(answ_vec[j]);
			BackPropagation(act_rate);
		}
	}
}

void FNN::Learn(int epoch, double act_rate, double b,bool trace)
{

	SetB(b);
	int test_count = 0;
	int test_check = 10;
	for (int i = 0; i < epoch; i++)
	{
		if (trace && test_count % test_check == 0)
		{
			cout << "Epoch#" << i << "Mistake " << Test() << endl;
		}

		for (int j = 0; j < inputs.size(); j++)
		{
			FeedForward(inputs[j]);
			GetMistake(targets[j]);
			BackPropagation(act_rate);
		}
		test_count++;
	}
}
void FNN::OldLearn(int epoch, double act_rate, double b, bool trace)
{
	SetB(b);
	int test_count = 0;
	int test_check = 10;
	for (int i = 0; i < epoch; i++)
	{
		if (trace && test_count % test_check == 0)
		{
			cout << "Epoch#" << i << "Mistake " << Test() << endl;
		}

		for (int j = 0; j < inputs.size(); j++)
		{
			FeedForward(inputs[j]);
			GetMistake(targets[j]);
			BackPropagation(act_rate);
		}
		test_count++;
	}
}
string FNN::GetTopology()
{
	string tmp;
	stringstream s;
	for (int i = 0; i < layers_count; i++)
	{
		s << layers[i]->size << " ";

	}
	tmp.append(s.str());
	return tmp;
}
vector<double> FNN::Normalize(double * inp, int size)
{
	NewMin = -1;
	NewMax = 1;
	OldMax = Max(inp, size);
	OldMin = Min(inp, size);

	double OldRange = (OldMax - OldMin);
	double	NewRange = (NewMax - NewMin);

	vector<double> tmp(size);

	for (int i = 0; i < size; i++)
	{
		tmp[i] = (((inp[i] - OldMin) * NewRange) / OldRange) + NewMin;
	}
	return tmp;
}
void FNN::Normalize(Sample & inp, bool set)
{
	if (inp.size() == 0)
		cout << "There is no data to Normolize!!!" << endl;

	mean = Mean(inp);
	OldMax = Max(inp);
	OldMin = Min(inp);
	std = Std(inp);

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
}

void FNN::Clear()
{
}

double FNN::Recover(double answ)
{
	double OldRange = (OldMax - OldMin);
	double	NewRange = (NewMax - NewMin);

	double OldValue = OldMin + (OldRange*(answ - NewMin)) / NewRange;
	return OldValue;
}





void FNN::Debug()
{
	/*for (int i = 0; i < size; i++)
	{
		cout << "Neuron #" << i << endl;
		for (int j = 0; j < pre_size + 1; j++)
		{
			cout << "Weight #" << j << " = " << weights[i][j] << endl;
		}
		cout << "Mistakes #" << i << " = " << mistakes[i] << endl;
	}*/
}

double FNN::Test(Sample & inp_vec, Sample & answ_vec)
{
	double sum = 0;
	double per = 0;
	int sample_size = answ_vec[0].size();
	for (int i = 0; i < answ_vec.size(); i++)
	{
		FeedForward(inp_vec[i]);
		for (int j = 0; j < sample_size; j++)
		{
			sum += abs(layers[layers_count - 1]->values[j] - answ_vec[i][j]);
			per += (1 - (layers[layers_count - 1]->values[j] - answ_vec[i][j])) / answ_vec[i][j];
		}
	}
	sum /= answ_vec.size();
	per /= answ_vec.size();
	cout.precision(4);
	cout << "TEST MISTAKE = " << sum << " per: " << per << "%" << endl;
	return sum;
}

double FNN::Test()
{
	double sum = 0;
	double per = 0;
	int sample_size = targets_t[0].size();
	for (int i = 0; i < targets_t.size(); i++)
	{
		FeedForward(inputs_t[i]);
		for (int j = 0; j < sample_size; j++)
		{
			sum += abs(layers[layers_count - 1]->values[j] - targets_t[i][j]);
			per += (1 - (layers[layers_count - 1]->values[j] - targets_t[i][j])) / targets_t[i][j];
		}
	}
	sum /= targets_t.size();
	per /= targets_t.size();
	cout.precision(4);
	cout << "TEST MISTAKE = " << sum << " per: " << per << "%" << endl;
	return sum;
}

void FNN::SetFact(Fact f)
{
	for (int i = 1; i < layers.size()-1; i++)
	{
		static_cast<hLayer*>(layers[i])->SetFact(f);
	}
}

int FNN::ExportWeights(char * filename, int name_size)
{
	char  strd[] = "dfd";

	fstream file(filename, fstream::in | fstream::out | fstream::trunc);

	if (!file.is_open())
	{
		cout << "Cannot create file!" << endl;
		file.close();
		return -1;
	}

	string s = GetTopology();
	file << s << endl;

	for (int i = 1; i < layers_count; i++)
	{
		file << static_cast<hLayer*>(layers[i])->GetWeights() << endl;
	}
	file.close();
	return 0;
}
