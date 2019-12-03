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
	double GetResult();
	void BackPropagation(double act_rate);
	void SetB(double _b);
	void Debug();
	double Test(Sample & inp_vec, Sample & answ_vec);
	double Test();
	void SetFact(Fact);
	int ExportWeights(char * filename, int name_size);
	void FeedForward(vector<double> &inp_vec);
	void FeedForward(vector<double> &&inp_vec);
	double FeedForward(double * inp, int size);
	int ImportWeights(char * filename, int name_size);
	void GetMistake(vector<double> &answ_vec);
	void Learn(Sample & inp_vec, Sample & answ_vec, int epoch, double act_rate,double b,bool trace = true);
	void OldLearn(Sample & inp_vec, Sample & answ_vec, int epoch, double act_rate,double b,bool trace = true);
	void Learn(int epoch, double act_rate,double b,bool trace = true);
	void OldLearn(int epoch, double act_rate,double b,bool trace = true);
	string GetTopology();
	void Normalize(Sample & imp,bool set = false);
	void Clear();
	vector<double> Normalize(double * inp, int size);
	double Recover(double answ);
	Sample inputs;
	Sample inputs_t;
	Sample targets;
	Sample targets_t;
	vector<double> inp_calc;
	vector<int> topology;
	int               inp_size;
private:
	double NewMin = -1;
	double NewMax = 1;
	double mean = -228;
	double OldMax = -228;
	double OldMin = -228;
	double std = -228;
	vector<bLayer*> layers;
	
	int               out_size;
	int               layers_count;
};

