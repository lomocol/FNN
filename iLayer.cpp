#include "stdafx.h"
#include "iLayer.h"


void iLayer::FeedForward(vector<double> inp_vec)
{
	for (size_t i = 0; i < size; i++)
	{
		values[i] = inp_vec[i];
	}
}

void iLayer::FeedForward(double * inp, int _size)
{
	for (size_t i = 0; i < _size; i++)
	{
		values[i] = inp[i];
	}
}



iLayer::iLayer(int size):bLayer(size)
{
	
}


iLayer::~iLayer()
{
}
