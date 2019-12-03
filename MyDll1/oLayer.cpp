#include "stdafx.h"
#include "oLayer.h"


oLayer::oLayer(int _size, bLayer * _pre_layer, Fact f) :hLayer(_size, _pre_layer, f)
{
}

void oLayer::GetMistake(vector<double> answ_vec)
{
	for (int i = 0; i < size; i++)
	{
		//mistakes[i] = (values[i]-answ[i])*(values[i]-answ[i]);
		//mistakes[i] = MathAbs(values[i]-answ[i]);
		mistakes[i] = (answ_vec[i] - values[i]);
	}
	PassMistake();
}

oLayer::~oLayer()
{
}
