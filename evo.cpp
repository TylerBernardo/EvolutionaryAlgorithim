//
// Created by tpixe on 5/3/2022.
//

#include "evo.h"

std::uniform_real_distribution<double> unif(0,1);
std::default_random_engine re;

MatrixXd combineMatrixRandom(MatrixXd &matrix1, MatrixXd &matrix2){
    int length = matrix1.rows(), height = matrix1.cols();
    MatrixXd output = MatrixXd::Zero(length,height);
    for(int r = 0; r < length; r++){
        for(int c = 0; c < length; c++){
            double ranNum = unif(re);
            if(ranNum <= .5){
                output(r,c) = matrix1(r,c);
            }else{
                output(r,c) = matrix2(r,c);
            }
        }
    }
    output = output + 0.5 * MatrixXd::Random(length,height);
    return output;
}

int compareFunction(Agent &a1, Agent &a2){
    return a1.reward >= a2.reward;
}

//take the top quarter of agents and repopulate from there
void crossover(Agent** agents,int length){
    int toKeep = std::round(length/4.0);
    std::uniform_int_distribution<int> iUnif(0,toKeep-1);
    for(int a = 0; a < length-toKeep; a++){
        //determine twoParents TODO: check to make sure parent1 != parent2
        Agent* parent1 = agents[iUnif(re)], *parent2 = agents[iUnif(re)];
        Network* network = (agents[a+toKeep]->network);
        for(int i = 0; i < network->length-1; i++){
            network->weights[i] = combineMatrixRandom(parent1->network->weights[i],parent2->network->weights[i]);
            network->bias[i] = combineMatrixRandom(parent1->network->bias[i],parent2->network->bias[i]);
        }
        network->bias[network->length-1] = combineMatrixRandom(parent1->network->bias[network->length-1],parent2->network->bias[network->length-1]);
        agents[a+toKeep]->network = network;
    }
}

//takes in the length of the input space, a function to generate the input space, the length of the output space, and a function to map net outputs to the gamespace, which then returns reward info.
Agent* learn(EvoController *controller, int populationSize, int generations ){
    /*
     * Might be unneeded
    int networkLength = 2 + controller->hiddenLayerCount;
    int *networkHeight = new int[networkLength];
    networkHeight[0] = controller->inputSpaceLength;
    networkHeight[networkLength-1] = controller->outputSpaceLength;
    for(int i = 1; i < networkLength - 2; i ++){
        networkHeight[i] = controller->hiddenLayers[i - 1];
    }
     */

    //main loop,
    for(int g = 1; g <= generations; g++){
        //loop through each agent
        for(int i = 0; i < populationSize - 1; i++){
            do{
                //evaluate the agent's network on the current state
                double* output;
                controller->agents[i]->network->calc(controller->genInputSpace(i),controller->inputSpaceLength,output, controller->outputSpaceLength);
                int reward = controller->state(output,i);
                //process reward here
                controller->agents[i]->reward += reward;
            }while(controller->agents[i]->endState());
        }
        //determine top performers
        std::sort((controller->agents[0]), ((controller->agents[populationSize-1])), compareFunction);
        //mutation happens here
        //compute stats about generation
        int bestScore = controller->agents[0]->reward;
        double averageScore = bestScore;
        for(int k = 1; k < populationSize; k++){
            averageScore += controller->agents[k]->reward;
        }
        averageScore = averageScore/populationSize;
        std::cout << "The best during generation " << g << " score was " << bestScore << " and the average score was " << averageScore << std::endl;
        crossover(controller->agents,populationSize);
        for(int a = 0; a < populationSize; a++){
            controller->agents[a]->reward = 0;
        }
    }
    return controller->agents[0];
}