#include "Net.h"

Net::~Net()
{
    int layersCount = layers.size();
    for(int i = 0; i < layersCount; i++)
    {
        std::vector<Neuron*> & currentLayer = layers.at(i);
        for(int k =0;k < currentLayer.size();k++)
        {
            delete currentLayer.at(k);
        }
    }
}

Net::Net(std::vector<int> TOPOLOGY,int ACTIVATION_FUN, double BETA)
{
    addLayer(TOPOLOGY.at(0), 0,0,0);
	for (auto it=TOPOLOGY.begin()+1;it!=TOPOLOGY.end();it++)
	{
        addLayer(*it,*(it-1),ACTIVATION_FUN,BETA);
	}
    this->topology = TOPOLOGY;
    output.resize(TOPOLOGY.back());
}

void Net::reset()
{
    for(int i = 1; i < layers.size(); ++i)
    {
        auto layer = layers.at(i);
        for(int k = 0; k < layer.size(); ++k)
        {
            layer.at(k)->initWeights();
        }
    }

}

void Net::feedFoward()
{
    std::vector<Neuron*>* proccesingLayer = &layers.at(1);
	for (int i = 1; i < topology.size(); i++)
	{
		for (int k = 0; k < proccesingLayer->size(); k++)
		{
            proccesingLayer->at(k)->calcOutput(proccesingLayer-1);
		}
		proccesingLayer++;
	}

    std::vector<Neuron*>* outputLayer = getLastLayer();
    for(int i = 0; i < outputLayer->size(); ++i)
    {
        this->output[i] = outputLayer->at(i)->getOutput();
    }
}

void Net::feedFoward(std::vector<double>& INDEX)
{
	this->setInputs(INDEX);
	this->feedFoward();
}

void Net::feedFoward(int INPUT_INDEX)
{
	this->setInputs(*trainData->getSamplePointer(INPUT_INDEX));
	this->feedFoward();
}


void Net::addLayer(int NEURONS_NUM, int WEIGHTS,int ACTIVATION_FUN, double BETA)
{
    std::vector<Neuron*> newLayer;
	Neuron * newNeuron;
	for (int i = 0; i < NEURONS_NUM; i++)
	{
        newNeuron = new Neuron(WEIGHTS,ACTIVATION_FUN,BETA);
        newLayer.push_back(newNeuron);
	}
	this->layers.push_back(newLayer);
}

void Net::showOutputs()
{
	auto outputLayer=&layers.at(topology.size()-1);

	for (int i = 0; i < topology.at(topology.size()-1); i++)
	{
        std::cout << outputLayer->at(i)->getOutput() << std::endl;
	}
}

void Net::setInputs(std::vector<double>& INDEX)
{
	int i = 0;
	for (auto it=INDEX.begin();it!=INDEX.end();it++,i++)
	{
        layers[0][i]->setOutput(*it);
	}
}

void Net::setTrainData(TrainingData * TRAIN_DATA)
{
	trainData = TRAIN_DATA;
}

std::vector<Neuron*>* Net::getLastLayer()
{
    std::vector<Neuron*>* lastLayerPointer = &layers.back();
	return lastLayerPointer;
}

std::vector<Neuron*>* Net::getFirstLayer()
{
    std::vector<Neuron*> * pointer = &this->layers.at(0);
	return pointer;
}

std::vector<std::vector<Neuron*>>* Net::getLayersPnt()
{
    std::vector<std::vector<Neuron*>>* pnt = &layers;
	return pnt;
}

std::vector<int>* Net::getTopology()
{
	auto outputPnt = &topology;
	return outputPnt;
}

std::vector<double>* Net::getOutput()
{
	auto outputPointer = &(this->output);
	return outputPointer;
}
