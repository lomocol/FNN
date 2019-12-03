#pragma once
#include "bLayer.h"

class iLayer :
	public bLayer
{
public:
	void FeedForward(vector<double> inp_vec);
	void FeedForward(double * inp,int size);
	
	iLayer(int size);
	~iLayer();
private:
};

