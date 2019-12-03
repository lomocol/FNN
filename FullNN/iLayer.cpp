#include "pch.h"
#include "iLayer.h"


void iLayer::FeedForward(vector<double> inp_vec)
{
	for (size_t i = 0; i < size; i++)
	{
		values[i] = inp_vec[i];
	}
}



iLayer::iLayer(int size):bLayer(size)
{
	
}


iLayer::~iLayer()
{
}
