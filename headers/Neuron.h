#pragma once
#include<vector>
#include<random>
#include<math.h>

enum transferFunctionType {logistic = 0, hiperbTan};

class Neuron
{
public:
	Neuron();
	~Neuron();
    Neuron(int WEIGHTS_QUANITY,int ACTIVATION_FUN, double BETA);
	void initWeights();

	double transferFunction(double ARG);
	double calcDerivative(double ARG);

    void calcOutput(std::vector<Neuron*>* LAYER);
	void calcOutputError(double TARGET_VAL);
    void calcHiddenError(std::vector<Neuron*>* NEXT_LAYER,int NEURON_INDEX);
    void updateWeights(std::vector<Neuron*>* PREV_LAYER);
	void addCorrections();

	//setters
	void setWeightAt(int INDEX,double VALUE);
	void setBiasWeight(double VALUE);
	void setOutput(double VALUE);
	void setError(double VALUE);
    static void setEta(double VALUE);
	//getters

	double getWeightAt(int INDEX);
	double getBiasWeight();
	double getOutput();
	int weightsNumber;
	double getError();
	std::vector<double>* getWeights();

	std::vector<double>* deltaWeights;
	double deltaBias;
private:
	std::vector<double> *weights;
	double biasWeight;
	double output;
	double error;
    double beta;
	transferFunctionType transferFun;
    static double eta;
};

