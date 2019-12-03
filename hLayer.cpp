#include "stdafx.h"
#include "hLayer.h"



hLayer::hLayer(int _size, bLayer * _pre_layer, Fact f):bLayer(_size)
{
	b = 1;
	F = f;
	pre_layer = _pre_layer;
	sum.resize(size);
	pre_size = pre_layer->size;
	mistakes.resize(size);
	weights.resize(size);
	
	for (size_t i = 0; i < size; i++)
	{
		weights[i].resize(pre_size + 1);
		for (size_t j = 0; j < pre_size + 1; j++)
		{
			weights[i][j] = fRand(-0.5,0.5);
		}
		mistakes[i] = -228;
	}
}

hLayer::~hLayer()
{
}

void hLayer::FeedForward()
{
	thread th();

	for (int i = 0; i < size; i++)
	{
		values[i] = 0;
		sum[i] = 0;
		for (int j = 0; j < pre_size+1; j++)
		{
			sum[i] += weights[i][j] * pre_layer->values[j];
		}
		//sum[i] += weights[i][pre_size] * 1;
		values[i] = F(sum[i] * b);
	}

}

void hLayer::OldFeedForward()
{
	for (int i = 0; i < size; i++)
	{
		values[i] = 0;
		sum[i] = 0;
		for (int j = 0; j < pre_size + 1; j++)
		{
			sum[i] += weights[i][j] * pre_layer->values[j];
		}
		//sum[i] += weights[i][pre_size] * 1;
		values[i] = F(sum[i] * b);
	}
}

void hLayer::PassMistake()
{
	fill(pre_layer->mistakes.begin(), pre_layer->mistakes.end(), 0);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < pre_size; j++)
		{
			pre_layer->mistakes[j] += mistakes[i] * weights[i][j];
		}
	}
}

void hLayer::SetFact(Fact f)
{
	F = f;
}

void hLayer::GetMistake()
{
	PassMistake();
}

void hLayer::SetWeights(vector<vector<double>>& file_weights)
{
	for (int i = 0; i < file_weights.size(); i++)
	{
		for (int j = 0; j < file_weights[0].size(); j++)
		{
			weights[i][j] = file_weights[i][j];
		}
	}
}

string hLayer::GetWeights()
{
	string tmp;
	stringstream s;
	for (int i = 0; i < weights.size(); i++)
	{
		for (int j = 0; j < weights[0].size(); j++)
		{
			s << weights[i][j] << endl;
		}
	}
	tmp.append(s.str());
	return tmp;
}

double hLayer::D(double _sum)
{
	return ((F(_sum) - F(_sum - h)) / h);
}

void hLayer::BackPropagation(double a)
{

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < pre_size+1; j++)
		{
			weights[i][j] += mistakes[i] * pre_layer->values[j] * D(sum[i])*a;
		}
		//weights[i][pre_size] += mistakes[i] * 1 * D(sum[i])*a;
	}

}






