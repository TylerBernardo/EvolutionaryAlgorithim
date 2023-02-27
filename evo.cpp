//
// Created by tpixe on 5/3/2022.
//

#include "evo.h"


//takes in the length of the input space, a function to generate the input space, the length of the output space, and a function to map net outputs to the gamespace, which then returns reward info
void learn(EvoController *controller, int populationSize, int generations ){
    int networkLength = 2 + controller->hiddenLayerCount;
    int *networkHeight = new int[networkLength];
    networkHeight[0] = controller->inputSpaceLength;
    networkHeight[networkLength-1] = controller->outputSpaceLength;
    for(int i = 1; i < networkLength - 2; i ++){
        networkHeight[i] = controller->hiddenLayers[i - 1];
    }
    //create array of agents
    Agent *agents;
    //initialize agents
    for(int i = 0; i < populationSize - 1; i++){
        agents[i] = *(controller->createAgent());//Network(networkLength,networkHeight);
    }
    //main loop,
    for(int g = 1; g < generations; g++){
        //loop through each agent
        for(int i = 0; i < populationSize - 1; i++){
            do{
                //evaluate the agent's network on the current state
                double* output;
                controller->agents[i].network.calc(controller->genInputSpace(i),controller->inputSpaceLength,output, controller->outputSpaceLength);
                int reward = controller->state(output);
                //process reward here
                controller->agents[i].reward += reward;
            }while(controller->agents[i].endState());
        }
        //mutation happens here

    }
}