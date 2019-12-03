#include <iostream>
#include "FNN.h"
#include "Genetic.h"

#define _DLLAPI extern "C" __declspec(dllexport)

_DLLAPI int __stdcall ExportNetworkToFile(char * filename,int name_size);
_DLLAPI int __stdcall ImportNetworkFromFile(char * filename,int name_size);
_DLLAPI int __stdcall Normalize();
_DLLAPI int __stdcall LoadClosePrices(char * c_name, int c_name_size, char * c_name_t, int c_name_size_t, int sample_size);
_DLLAPI int __stdcall CreateMeanAnswers(int answer_diaposon);
_DLLAPI int __stdcall CreateSin(int size, int test_size);
_DLLAPI double __stdcall FeedForward(double * inp, int size);
_DLLAPI void __stdcall Learn(int epoch, double act_rate, double b,bool trace = true);
_DLLAPI void __stdcall OldLearn(int epoch, double act_rate, double b,bool trace = true);
_DLLAPI double __stdcall Test();
_DLLAPI double __stdcall Check();
_DLLAPI void __stdcall GeneticAlgoritm(int batch_size,int epoch,bool mutation = true,bool multi = true);
_DLLAPI void __stdcall SetFact(int fn);
_DLLAPI int __stdcall LoadVectorOfPrices(char * c_name, int c_name_size);
_DLLAPI void __stdcall AddInputLayer(int size);
_DLLAPI double *   __stdcall GetPrices(int & count);
_DLLAPI void __stdcall AddFullLayer(int size, int f_num);
_DLLAPI void __stdcall AddOutLayer(int size, int f_num);
_DLLAPI void __stdcall  Calculate(double * buffer, int buf_size, double * prices, int prices_size);

_DLLAPI int fibonacci_init(int x);