#include "stdafx.h"
#include "bLayer.h"


bLayer::bLayer(int _size)
{
	size = _size;
	values.resize(size+1);
	values[size] = 1;
}


bLayer::~bLayer()
{
}

