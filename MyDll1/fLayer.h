#pragma once
#include "hLayer.h"
class fLayer :
	public hLayer
{
public:
	fLayer(int _size, bLayer * pre_layer, Fact f);
	~fLayer();
};

