#pragma once
#include <iostream>
#include "functions.h"
using namespace functions;

using namespace std;

typedef double (*Fact)(double);





class bLayer
{
public:
	bLayer(int _size);
	~bLayer();
	virtual void FeedForward() { cout << " Method FeedForward was colled for Base Class bLayer!!! " <<endl; };
	virtual void GetMistake() { cout << " Method PassMistake was colled for Base Class bLayer!!! " <<endl; };
	virtual void BackPropagation(double act_rate) { cout << " Method BackPropagation was colled for Base Class bLayer!!! " <<endl; };
	int size;
	vector<double> mistakes;
	vector<double> values;
};

