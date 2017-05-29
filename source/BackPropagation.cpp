#include "BackPropagation.h"
#include"BackPropObserver.h"
template<typename T>
std::vector<T> operator-(std::vector<T> &A, std::vector<T> &B)
{
	std::vector<T> C(A.size(), 0);
	for (int i = 0; i < A.size();i++)
	{
		C.at(i) = A.at(i) - B.at(i);
	}
	return C;
}


BackPropagation::BackPropagation()
{
}


BackPropagation::~BackPropagation()
{
}

BackPropagation::BackPropagation(Net&  TARGET_NET,TrainingData&  TARGET_DATA)
{
	net = &TARGET_NET;
	trainData = &TARGET_DATA;
}

void BackPropagation::calcNeuronWeightsCorrection()
{
    std::vector<Neuron*>* lastLayer = net->getLastLayer();
    for (std::vector<Neuron*>* currentLayer = lastLayer;
		currentLayer != net->getFirstLayer();
		currentLayer--)
	{
        std::vector<Neuron*>* prevLayer = currentLayer - 1;
		for (int i = 0; i < currentLayer->size(); ++i)
		{
            Neuron* neuron = currentLayer->at(i);
            neuron->updateWeights(prevLayer);
		}
	}
}

void BackPropagation::addWeightsCorrection()
{
    std::vector<Neuron*>* lastLayer = net->getLastLayer();
    for (std::vector<Neuron*>* currentLayer = lastLayer;
		currentLayer != net->getFirstLayer();
		currentLayer--)
    {
        for (int i = 0; i < currentLayer->size(); ++i)
		{
            Neuron* neuron = currentLayer->at(i);
            neuron->addCorrections();
		}
	}
}

void BackPropagation::propagateError(std::vector<double>* const TARGET)
{
	//CALC OUTPUT ERROR
    std::vector<Neuron*>* lastLayer = net->getLastLayer();
	for (int i = 0; i < lastLayer->size(); ++i)
	{
        Neuron* neuron = lastLayer->at(i);
        neuron->calcOutputError(TARGET->at(i));
	}

	//CALC HIDDEN LAYERS ERROR
    for (std::vector<Neuron*>* currentLayer = lastLayer - 1;
		currentLayer != net->getFirstLayer();
		currentLayer--)
	{
        std::vector<Neuron*>* nextLayer = currentLayer + 1;
		for (int i = 0; i < currentLayer->size(); ++i)
		{
            currentLayer->at(i)->calcHiddenError(nextLayer,i);
		}
	}
}

double BackPropagation::calcRMSError(int SAMPLE_IDX )
{
	auto inputs = trainData->getSamplePointer(SAMPLE_IDX);
	auto targets = trainData->getTargetPointer(SAMPLE_IDX);

	net->feedFoward(*inputs);
    std::vector<Neuron*>* outputLayer =net->getLastLayer();
	
	double error = 0.0;
	for (int i = 0; i < outputLayer->size(); ++i)
	{
        double diff = targets->at(i) - outputLayer->at(i)->getOutput();
		error += pow(diff,2);
	}

    error = sqrt(error);
	return error;

}

double BackPropagation::calcRMSError()
{
	double rmsError = 0.0;
	for (int i = 0; i < trainData->getSamplesNumber(); ++i)
	{
		rmsError += calcRMSError(i);
	}
    error = rmsError / trainData->getSamplesNumber();
    errorVector.push_back(error);
	return rmsError;
}

void BackPropagation::calcLastLayerError(std::vector<double>* TARGET)
{
    std::vector<Neuron*>* lastLayer = net->getLastLayer();
	for (int i = 0; i < lastLayer->size(); ++i)
	{
        Neuron* neuron = lastLayer->at(i);
        neuron->calcOutputError(TARGET->at(i));
	}
}

int BackPropagation::randomExample()
{
	auto trainData=this->getTrainData();
	int samplesNumber = trainData->getSamplesNumber();
	std::random_device rd;
	std::uniform_real_distribution<double> generator(0, samplesNumber);
	return generator(rd);
	
}

void BackPropagation::onlineTrain()
{
    error = 0.1;
    epochNumber = 0;
	int sampleNumber=0;
	std::vector<double>* sample;
	std::vector<double>* target;
    while (error > 0.01 && epochNumber < 10000)
	{
		sampleNumber=this->randomExample();

		sample = trainData->getSamplePointer(sampleNumber);
		target = trainData->getTargetPointer(sampleNumber);
        net->feedFoward(*sample);
        propagateError(target);
		calcNeuronWeightsCorrection();
		addWeightsCorrection();
        calcRMSError();
		epochNumber++;
        notifyObserver();
	}
}

void BackPropagation::batchTrain()
{
    epochNumber = 0;
    error = 0.1;
    while (error > 0.01 && epochNumber < 10000)
	{
		std::vector<int> order = trainData->shuffleSamples();
		std::vector<double>* sample;
		std::vector<double>* target;
		for (auto index : order)
		{
			sample = trainData->getSamplePointer(index);
			target = trainData->getTargetPointer(index);
			net->feedFoward(*sample);
			propagateError(target);
			calcNeuronWeightsCorrection();
		}
		addWeightsCorrection();
        calcRMSError();

		epochNumber++;
        notifyObserver();
	}
}

void BackPropagation::showErrors()
{
	auto lastLayer = net->getLastLayer();
	for (int i=0;i<lastLayer->size();i++)
	{
        std::cout <<"error: "<< lastLayer->at(i)->getError() << std::endl;
    }
}

void BackPropagation::addObserver(BackPropObserver *obs)
{
    observer = obs;
}

void BackPropagation::notifyObserver()
{
    observer->update(epochNumber,error);
}

void BackPropagation::reset()
{
    net->reset();
    errorVector.clear();
}


TrainingData * BackPropagation::getTrainData()
{
	TrainingData* pointer=this->trainData;
	
    return pointer;
}

std::vector<double> &BackPropagation::getErrorVector()
{
    return errorVector;
}

Net *BackPropagation::getNet()
{
    Net* netPnt = this->net;
    return netPnt;
}
