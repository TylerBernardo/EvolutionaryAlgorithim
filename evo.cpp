//
// Created by tpixe on 5/3/2022.
//

#include "evo.h"


//takes in the length of the input space, a function to generate the input space, the length of the output space, and a function to map net outputs to the gamespace, which then returns reward info
void learn(int inputSpaceLength, EvoController *controller, int outputSpaceLength, int populationSize, int hiddenLayerNum, int *hiddenLayers, int generations ){
    int networkLength = 2 + hiddenLayerNum;
    int *networkHeight = new int[networkLength];
    networkHeight[0] = inputSpaceLength;
    networkHeight[networkLength-1] = outputSpaceLength;
    for(int i = 1; i < networkLength - 2; i ++){
        networkHeight[i] = hiddenLayers[i - 1];
    }
    //create array of agents
    Network *agents = new Network[populationSize];
    //initialize agents
    for(int i = 0; i < populationSize - 1; i++){
        agents[i] = Network(networkLength,networkHeight);
    }
    //main loop
    for(int g = 1; g < generations; g++){

    }
}