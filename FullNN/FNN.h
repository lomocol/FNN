#pragma once
#include "iLayer.h"
#include "fLayer.h"
#include "oLayer.h"

class FNN
{
public:
	FNN();
	~FNN();
	void AddInputLayer(int size);
	void AddFullLayer(int size,Fact f);
	void AddOutLayer(int size,Fact f);
	void BackPropagation(double act_rate);
	void SetB(double _b);
	void Debug();
	void Test(Sample & inp_vec, Sample & answ_vec);
	void FeedForward(vector<double> &inp_vec);
	void GetMistake(vector<double> &answ_vec);
	void Learn(Sample & inp_vec, Sample & answ_vec, int epoch, double act_rate,double b);
private:
	vector<bLayer*> layers;
	int               inp_size;
	int               out_size;
	int               layers_count;
};

