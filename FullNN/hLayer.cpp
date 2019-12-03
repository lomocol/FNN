#include "pch.h"
#include "hLayer.h"



hLayer::hLayer(int _size, bLayer * _pre_layer, Fact f):bLayer(_size)
{
	b = 1;
	F = f;
	sum.resize(size);
	pre_size = _pre_layer->size;
	mistakes.resize(_size);
	weights.resize(_size);
	pre_layer = _pre_layer;
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
	for (int i = 0; i < size; i++)
	{
		values[i] = 0;
		sum[i] = 0;
		for (int j = 0; j < pre_size; j++)
		{
			sum[i] += weights[i][j] * pre_layer->values[j];
		}
		sum[i] += weights[i][pre_size] * 1;
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

void hLayer::GetMistake()
{
	PassMistake();
}

double hLayer::D(double _sum)
{
	return ((F(_sum) - F(_sum - h)) / h);
}

void hLayer::BackPropagation(double a)
{

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < pre_size; j++)
		{
			weights[i][j] += mistakes[i] * pre_layer->values[j] * D(sum[i])*a;
		}
		weights[i][pre_size] += mistakes[i] * 1 * D(sum[i])*a;
	}

}






