#pragma once
#include "hLayer.h"
class oLayer :
	public hLayer
{
public:
	oLayer(int _size, bLayer * pre_layer, Fact f);
	void GetMistake(vector<double> answ_vec);
	~oLayer();
};

