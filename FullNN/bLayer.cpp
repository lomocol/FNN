#include "pch.h"
#include "bLayer.h"


bLayer::bLayer(int _size)
{
	size = _size;
	values.resize(size);
}


bLayer::~bLayer()
{
}

