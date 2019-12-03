#pragma once
#include "bLayer.h"

static const double h = 0.001;

class hLayer :
	public bLayer
{
public:
	hLayer(int _size,bLayer*_pre_layer,Fact f);
	~hLayer();
	void FeedForward();
	void OldFeedForward();
	double D(double);
	void PassMistake() ;
	void SetFact(Fact f);
	void GetMistake() ;
	void SetWeights(vector<vector<double>> & file_weights);
	string GetWeights();
	void BackPropagation(double a);
	//void Debug();
	double b;
protected:
	int pre_size;
	bLayer * pre_layer;
	Fact F;
	vector<double> sum;
	vector<vector<double>> weights;
};

