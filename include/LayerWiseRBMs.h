#ifndef _LAYERWISERBMS_H_
#define _LAYERWISERBMS_H_

#include "RBM.h"
#include "IModel.h"
#include "MLP.h"

/*
 * stackRBMs, 也即是DBN的与训练部分
 */
class LayerWiseRBMs : public LayerWiseModel {
	public:
		LayerWiseRBMs();
		LayerWiseRBMs(int n, int sizes[]);
		LayerWiseRBMs(const char * fileName);
		void setPersistent(bool f);
		void addLayer(RBM * layer);
		void saveModel(FILE *fp);
		void setGuassVisible(bool f){
			for(int i=0; i<numLayers; i++){
				layers[i]->setGuassVisible(f);
			}
		}
		void setGuassHidden(bool f){
			for(int i=0; i<numLayers; i++){
				layers[i]->setGuassHidden(f);
			}
		}
		~LayerWiseRBMs();
		
		int getNumLayer(){ return numLayers; }
		IModel *getLayerModel(int i){ return layers[i]; }
		void toMLP(MLP *mlp, int numLabel);	//预训练结束之后,权重值赋给MLP
		
		void activitionMaximization(int layerIdx, double argvNorm, int epoch, char *AMSampleFile);
	private:
		int numLayers;	    				//模型层数
		int unitSizes[maxLayer+1];			//每层节点单元数
		RBM *layers[maxLayer];
		void loadModel(FILE *fp);

//		激励最大化
		double maximizeUnit(int layerIdx, int unitIdx, double*unitSample, double argvNorm, int epoch);
		void saveSample(FILE *fp, double *s, int n);
		double *AMSample;
};
#endif
