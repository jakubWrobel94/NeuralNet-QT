#ifndef BACKPROPOBSERVER_H
#define BACKPROPOBSERVER_H

class BackPropagation;
class QLabel;
class QProgressBar;
class BackPropObserver
{
public:
    BackPropObserver(BackPropagation* backProp,QLabel* epoch,QLabel* error,QProgressBar* progBar);
    void update(int &epochNum, double &error);
private:
    int epochNumber;
    double errorValue;
    BackPropagation* backPropagation;
    QLabel* epochLabel;
    QLabel* errorLabel;
    QProgressBar* progressBar;
};

#endif // BACKPROPOBSERVER_H
