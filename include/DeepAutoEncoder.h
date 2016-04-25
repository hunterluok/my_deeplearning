#ifndef _DEEPAUTOENCODER_H_
#define _DEEPAUTOENCODER_H_

#include "EncoderLayer.h"

class DeepAutoEncoder : public UnsuperviseModel {
	public:
		DeepAutoEncoder();
		DeepAutoEncoder(int n, int sizes[]);
		DeepAutoEncoder(const char * filename);
		~DeepAutoEncoder();
		void setLearningRate(double lrt);
		void setBatchSize(int size);
		void setInput(double *in){ layers[0]->setInput(in); }
//设置输入输出是实值还是二值分布
        void setGaussIn(bool f){
        	layers[0]->setGaussIn(f);
        }
        void setGaussOut(bool f){
        	layers[0]->setGaussOut(f);
        }

		void trainBatch();		//训练模型
		void runBatch();
		double getTrainingCost();

		int getLayerNumber(){ return numLayers; }
		int getInputNumber(){ return layers[0]->getInputNumber(); }
		int getOutputNumber(){ return layers[numLayers-1]->getOutputNumber(); }
		double * getOutput(){ return layers[numLayers-1]->getOutput(); }

		void saveModel(FILE *fp);

		void activationMaximization(int layerIdx, double avgNorm, int epoch,
                char amSampleFile[]);
	private:
		int numLayers;
		int unitSizes[maxLayer+1];
		EncoderLayer * layers[maxLayer];

		void mallocMemory();	// 内存分配
		void forward();			//前向
		void backpropagate();	//后向求导更新权重
		void loadModel(FILE *fp);

		int batchSize;

//      激励最大化
        double maximizeUnit(int layerIdx, int unitIdx, double*unitSample, double argvNorm, int epoch);
        void saveSample(FILE *fp, double *s, int n); //存储最终的sample
        double *AMSample;

};

#endif
