#pragma once
#include "bLayer.h"

class iLayer :
	public bLayer
{
public:
	void FeedForward(vector<double> inp_vec);
	
	iLayer(int size);
	~iLayer();
private:
};

