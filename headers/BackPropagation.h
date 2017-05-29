#pragma once
#include<vector>
#include"Neuron.h"
#include"Net.h"
#include"TrainingData.h"

class BackPropObserver;

class BackPropagation
{
public:
	BackPropagation();
	~BackPropagation();
	BackPropagation(Net&  TARGET_NET, TrainingData&  TARGET_DATA);

	void calcNeuronWeightsCorrection();
	void addWeightsCorrection();

	void propagateError(std::vector<double>* const TARGET);
	double calcRMSError(int SAMPLE_IDX);
	double calcRMSError();
	void calcLastLayerError(std::vector<double>* const TARGET);

	int randomExample();

	void onlineTrain();
	void batchTrain();

	void showErrors();

    void addObserver(BackPropObserver* obs);
    void notifyObserver();

    void reset();

	TrainingData* getTrainData();
    std::vector<double>& getErrorVector();
    Net* getNet();
private:
	Net * net;
	TrainingData* trainData;
    int epochNumber;
    double error;

	std::vector<double>* targetPointer;
    std::vector<double> errorVector;
    BackPropObserver* observer;


};

