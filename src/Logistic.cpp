#include "Logistic.h"
#include <cmath>
#include <cstdio>

Logistic::Logistic(int numIN, int numOut):softmaxLayer(numIn, numOut), SuperviseModel(){}
Logistic::Logistic(const shar * fileName):softmaxLayer(fileName), SuperviseModel(){}

void Logistic::trainBatch(){
	forward();
	backpropagate(NULL);
}
void Logistic::runBatch(){
	forward();
}

double Logistic::getTrainingCost(){
	double cost =0.0;
	double *y = getOutput();
	for(int i=0; i<batchSize*numOut; ++i){
		cost += -1 * label[i] * log(1-y[i]);
	}
	return cost/batchSize;
}

void Logistic::computeDelta(Layer * prevLayer){
	if(prevLayer==NULL){
		double * y= getOutput();
		cbals_dcopy(batchSize*numOut, y, 1, delta, 1);
		cbals_daxpy(batchSize*numOut, -1.0, label, 1, delta, 1);
	}
	else{
		printf("wrong back, no prev layer\n");
	}
}
void Logistic::saveModel(FILE* fp){
	Layer::saveModel(fp);
}