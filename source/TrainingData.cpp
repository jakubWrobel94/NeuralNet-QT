#include "TrainingData.h"
#include<sstream>


TrainingData::TrainingData()
{
	samplesNumber = 0;
}

TrainingData::TrainingData(std::string INPUT_PATH, std::string OUTPUT_PATH)
{
	samplesNumber = 0;
	loadIputFromFile(INPUT_PATH);
	loadOutputFromFile(OUTPUT_PATH);
}


TrainingData::~TrainingData()
{
}

void TrainingData::loadIputFromFile(std::string INPUT_PATH)
{
	std::fstream inputFile;
	inputFile.open(INPUT_PATH);
	if (inputFile.good())
	{
        /*std::string line;
		int numberOfNeurons;
		inputFile >> numberOfNeurons;
		while (!inputFile.eof())
		{
			std::vector<double> samples;
			int sample;
			for (int i = 0; i < numberOfNeurons; ++i)
			{
				inputFile >> sample;
				samples.push_back(sample);
			}
			addSample(samples);
		}
        */
        std::string line;
        while(!inputFile.eof())
        {

        std::getline(inputFile,line);
        std::istringstream stringStream(line);
        std::string valueString;
        std::vector<double> samples;
        while(stringStream>>valueString)
        {
            double valueDouble = std::stod(valueString);
            samples.push_back(valueDouble);
        }
        addSample(samples);
        }

    }

}

void TrainingData::loadOutputFromFile(std::string OUTPUT_PATH)
{
	std::fstream outputFile;
	outputFile.open(OUTPUT_PATH);
	if (outputFile.good())
	{
        /*std::string line;
		int numberOfNeurons;
		outputFile>> numberOfNeurons;
		while (!outputFile.eof())
		{
			std::vector<double> samples;
			int sample;
			for (int i = 0; i < numberOfNeurons; ++i)
			{
				outputFile>> sample;
				samples.push_back(sample);
			}
            addTarget(samples);
        }*/
        std::string line;
        while(!outputFile.eof())
        {

        std::getline(outputFile,line);
        std::istringstream stringStream(line);
        std::string valueString;
        std::vector<double> samples;
        while(stringStream>>valueString)
        {
            double valueDouble = std::stod(valueString);
            samples.push_back(valueDouble);
        }
        addTarget(samples);
        }
	}
}

void TrainingData::addSample(std::vector<double>& SAMPLE)
{
	this->samples.push_back(SAMPLE);
	samplesNumber++;
}

void TrainingData::addTarget(std::vector<double>& SAMPLE)
{
	this->targets.push_back(SAMPLE);
}

std::vector<double>* TrainingData::getSamplePointer(int INDEX)
{
	auto pointer = &this->samples.at(INDEX);
	return pointer;
}

std::vector<double>* TrainingData::getTargetPointer(int INDEX)
{
	auto pointer = &this->targets.at(INDEX);
	return pointer;
}

std::vector<int> TrainingData::shuffleSamples()
{
	std::vector<int> indexVector;
	std::vector<int> outputVector;
	for (int i = 0; i < this->samplesNumber; i++)
	{
		indexVector.push_back(i);
	}
	int a = samplesNumber;
	std::random_device rd;
	for (int i = 0; i < this->samplesNumber; i++)
	{
	
		std::uniform_real_distribution<double> generator(0, a-1);
		int index=generator(rd);
		outputVector.push_back(indexVector.at(index));
		indexVector.erase(indexVector.begin()+index);
		a--;
	}
	return outputVector;
}

int TrainingData::getSamplesNumber()
{
	return this->samplesNumber;
}
