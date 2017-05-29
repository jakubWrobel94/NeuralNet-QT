#pragma once
#include<vector>
#include"Neuron.h"
#include<iostream>
#include"TrainingData.h"

class Net
{
public:
	~Net();
    Net(std::vector<int> TOPOLOGY,int ACTIVATION_FUN,double BETA);
    void reset();
	void feedFoward();
	void feedFoward(std::vector<double> &INPUTS);
	void feedFoward(int INPUT_INDEX);

    void addLayer(int NEURONS_NUM,int WEIGHTS, int ACTIVATION_FUN,double BETA);
	void showOutputs();
	
	void setInputs(std::vector<double> &INDEX);
	void setTrainData(TrainingData* TRAIN_DATA);
	//getters
    std::vector < std::vector<Neuron* >>* getLayersPnt();
	std::vector<int> * getTopology();
	std::vector<double> * getOutput();
    std::vector<Neuron*>* getLastLayer();
    std::vector<Neuron*>* getFirstLayer();
private:
    std::vector < std::vector<Neuron*>> layers;
	std::vector<int> topology;
	std::vector<double> output;
	TrainingData* trainData;
};

