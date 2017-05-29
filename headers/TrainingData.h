#pragma once
#include<vector>
#include<random>
#include<iostream>
#include<fstream>
#include<string>
class TrainingData
{
public:
	TrainingData();
	TrainingData(std::string INPUT_PATH, std::string OUTPUT_PATH);
	~TrainingData();

	void loadIputFromFile(std::string INPUT_PATH);
	void loadOutputFromFile(std::string OUTPUT_PATH);
	void addSample(std::vector<double> &SAMPLE);
	void addTarget(std::vector<double> &SAMPLE);

	//getters
	std::vector<double>* getSamplePointer(int INDEX);
	std::vector<double>* getTargetPointer(int INDEX);

	std::vector<int> shuffleSamples();
	int getSamplesNumber();

private:
	int samplesNumber;
	std::vector<std::vector<double>> samples;
	std::vector<std::vector<double>> targets;

};

