#include "BackPropObserver.h"
#include"QLabel"
#include"BackPropagation.h"
#include"QProgressBar"

BackPropObserver::BackPropObserver(BackPropagation* backProp,QLabel* epoch,QLabel* error,QProgressBar* progBar)
{
    backPropagation = backProp;
    backPropagation->addObserver(this);
    epochLabel = epoch;
    errorLabel = error;
    progressBar = progBar;

}

void BackPropObserver::update(int &epochNum, double &error)
{
    this->epochNumber = epochNum;
    progressBar->setValue(epochNumber);
    this->errorValue = error;
    epochLabel->setText(QString::number(epochNumber));
    errorLabel->setText(QString::number(errorValue));
}
