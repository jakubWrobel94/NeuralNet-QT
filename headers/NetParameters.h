#ifndef NETPARAMETERS_H
#define NETPARAMETERS_H

struct NetParameters{

    std::vector<int> netTopology;
    int activationFunction; //0 - log, 1 - tangh
    double beta;
};
#endif // NETPARAMETERS_H
