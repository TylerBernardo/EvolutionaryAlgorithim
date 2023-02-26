//
// Created by tpixe on 5/3/2022.
//

#ifndef EVOLUTIONARYALGORITHIM_EVO_H
#define EVOLUTIONARYALGORITHIM_EVO_H
#include <Eigen/Dense>
#include<cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>
#include "newNetwork.h"
using namespace Eigen;

class Agent{
public:
    Agent(){

    }
};

class EvoController{
    Agent *agents;
    public:
        EvoController(){

        }

        virtual int* genInputSpace();
        virtual int state(double *output, int length);
};



void learn(int inputSpaceLength, EvoController *controller, int outputSpaceLength, int populationSize, int hiddenLayerNum, int *hiddenLayers, int generations );

#endif //EVOLUTIONARYALGORITHIM_EVO_H
