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

//pure virtual class to allow scene specific actions to be made.
class Agent{
    int inputSpaceLength, outputSpaceLength, hiddenLayerCount;
    public:
        Agent(){

        }
};
//pure virtual class
class EvoController{

    public:

    Agent *agents;
        EvoController(){

        }

        virtual int* genInputSpace();
        virtual int state(double *output, int length);
};



void learn(int inputSpaceLength, EvoController *controller, int outputSpaceLength, int populationSize, int hiddenLayerNum, int *hiddenLayers, int generations );

#endif //EVOLUTIONARYALGORITHIM_EVO_H
