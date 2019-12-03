#include "pch.h"
#include "FNN.h"

FNN::FNN()
{
	inp_size = 0;
	out_size = 0;
	layers_count = 0;
}

FNN::~FNN()
{

}

void FNN::AddInputLayer(int size)
{
	inp_size = size;
	layers.push_back(new iLayer(size));
	layers_count++;
}

void FNN::AddFullLayer(int size, Fact f)
{
	layers.push_back(new fLayer(size, layers.back(),f));
	layers_count++;
}

void FNN::AddOutLayer(int size, Fact f)
{
	out_size = size;
	layers.push_back(new oLayer(size, layers.back(), f));
	layers_count++;
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

void FNN::GetMistake(vector<double>& answ_vec)
{

	static_cast<oLayer*>(layers[layers_count - 1])->GetMistake(answ_vec);
	for (int i = layers_count - 2; i > 1; i--)
	{
		layers[i]->GetMistake();
	}

}

void FNN::Learn(vector<vector<double>>& inp_vec, vector<vector<double>>& answ_vec, int epoch, double act_rate, double b)
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

void FNN::Test(Sample & inp_vec, Sample & answ_vec)
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
}
