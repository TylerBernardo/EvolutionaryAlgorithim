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
#include <random>
#include <thread>
#include "newNetwork.h"
using namespace Eigen;

//pure virtual class to allow scene specific actions to be made.
class Agent{
    protected:
        int inputSpaceLength, outputSpaceLength, hiddenLayerCount;
    public:
        Network *network = nullptr;
        int reward = 0;
        //should the simulation end? Returns true when it should
        virtual bool endState(){return false;};

        ~Agent(){
            //delete network;
        }
};
//pure virtual class
class EvoController{

    public:
    int inputSpaceLength, outputSpaceLength, hiddenLayerCount;
    int *hiddenLayers;
    Agent **agents;
    int agentCount;

        /* base variables required for evoController;
        EvoController(int _inputSpaceLength, int _outputSpaceLength, int _hiddenLayerCount){
            this->inputSpaceLength = _inputSpaceLength;
            this->outputSpaceLength = _outputSpaceLength;
            this ->hiddenLayerCount = _hiddenLayerCount;
            this->hiddenLayers = new int[this->hiddenLayerCount];
        }*/
        //should return an array of length "inputSpaceLength" that represents all the inputs for the net of the agent located at agents[i]
        virtual double* genInputSpace(int agentNumber){return nullptr;};
        //should take in the output of the neural net and determine what action to take. Should take that action, then return score. also in charge of termination the simulation.
        virtual int state(double *output, int agentNumber){return 0;};
        //creates an agent
        virtual Agent* createAgent(){return nullptr;};
        //reset agent at agents[agentNum]
        virtual void reset(int agentNum){};

};



Agent* learn(EvoController *controller, int populationSize, int generations, int threads );

#endif //EVOLUTIONARYALGORITHIM_EVO_H
