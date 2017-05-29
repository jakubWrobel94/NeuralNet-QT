#include "Neuron.h"
double Neuron::eta= 0.1;
template<typename T>
std::vector<T> operator+(std::vector<T> &A, std::vector<T> &B)
{
	std::vector<T> C(A.size(), 0);
	for (int i = 0; i < A.size(); ++i)
	{
		C.at(i) = A.at(i) + B.at(i);
	}
	return C;
}

template<typename T>
std::vector<T> operator-(std::vector<T> &A, std::vector<T> &B)
{
	std::vector<T> C(A.size(), 0);
	for (int i = 0; i < A.size(); ++i)
	{
		C.at(i) = A.at(i) - B.at(i);
	}
	return C;
}

Neuron::Neuron()
{
}


Neuron::~Neuron()
{
}

Neuron::Neuron(int WEIGHTS_QUANITY,int ACTIVATION_FUN, double BETA)
{
    beta = BETA;
	this->weights=new std::vector<double>(WEIGHTS_QUANITY, 0);
	deltaWeights = new std::vector<double>(WEIGHTS_QUANITY, 0);
	deltaBias = 0;
	this->initWeights();
	this->weightsNumber = WEIGHTS_QUANITY;
    if(ACTIVATION_FUN == 0)transferFun = logistic;
    if(ACTIVATION_FUN == 1)transferFun = hiperbTan;
}

void Neuron::initWeights()
{
	std::random_device rd;
    std::uniform_real_distribution<double> generator(-0.2, 0.2);
	int index = 0;
	for (auto i=weights->begin();i!=weights->end(); ++i)
	{
		double value = generator(rd);
		setWeightAt(index,value);
		index++;
	}
	setBiasWeight(generator(rd));
}

double Neuron::transferFunction(double ARG)
{
    if(transferFun == logistic)
    {
        double expVal = exp(beta*ARG*(-1.0));
        return 1.0/(1.0+expVal);
    }
    if(transferFun == hiperbTan)
        return tanh(beta*ARG);
}

double Neuron::calcDerivative(double ARG)
{
    if (transferFun == logistic)
        return beta*transferFunction(ARG)*(1.0-transferFunction(ARG));
    if (transferFun == hiperbTan)
        return beta*(1.0 - (pow(transferFunction(ARG),2.0)));
}

void Neuron::calcOutput(std::vector<Neuron*>* LAYER)
{
	double output = 0.0;
	for (int i=0;i<weights->size();i++)
	{
        output += LAYER->at(i)->getOutput()*weights->at(i);
	}
	output += this->biasWeight;
	output = this->transferFunction(output);
	this->setOutput(output);
}

void Neuron::calcOutputError(double TARGET_VAL)
{
	this->getOutput();
    double errorVal = (output - TARGET_VAL)*calcDerivative(output);
    this->error=errorVal;
}

void Neuron::calcHiddenError(std::vector<Neuron*>* NEXT_LAYER,int NEURON_INDEX)
{
	double errorSum = 0.0;
	for (int i = 0; i < NEXT_LAYER->size(); ++i)
	{
        errorSum += NEXT_LAYER->at(i)->weights->at(NEURON_INDEX)*NEXT_LAYER->at(i)->getError();
	}
	errorSum *= calcDerivative(output);
	error = errorSum;
}

void Neuron::updateWeights(std::vector<Neuron*>* PREV_LAYER)
{
	for (int i = 0; i < weights->size(); ++i)
	{
        double newWeight = eta*error*PREV_LAYER->at(i)->getOutput() + 0.5*deltaWeights->at(i);
        deltaWeights->at(i) = newWeight;

	}

    double newDeltaBias = eta*error + 0.5*deltaBias;
    deltaBias = newDeltaBias;
}



void Neuron::addCorrections()
{
    *weights=*weights - *deltaWeights;
    biasWeight = biasWeight - deltaBias;
}

void Neuron::setWeightAt(int INDEX,double VALUE)
{
	this->weights->at(INDEX) = VALUE;
}

void Neuron::setBiasWeight(double VALUE)
{
	this->biasWeight = VALUE;
}

void Neuron::setOutput(double VALUE)
{
	this->output = VALUE;
}

void Neuron::setError(double VALUE)
{
    this->error = VALUE;
}

void Neuron::setEta(double VALUE)
{
    eta = VALUE;
}

double Neuron::getWeightAt(int INDEX)
{
	return this->weights->at(INDEX);
}

double Neuron::getBiasWeight()
{
	return this->biasWeight;
}

double Neuron::getOutput()
{
	return this->output;
}

double Neuron::getError()
{
	return this->error;
}

std::vector<double>* Neuron::getWeights()
{
	auto pointer = this->weights;
	return pointer;
}
