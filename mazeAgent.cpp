//
// Created by tyler on 3/7/2023.
//

#include "mazeAgent.h"

//TODO:hidden layers should only be used for hidden layer heights, add input and outpuyt length to start/end of that array
MazeAgent *MazeController::createAgent() {
   MazeAgent* toReturn = new MazeAgent(this->makeMaze(),this->inputSpaceLength,this->outputSpaceLength,this->hiddenLayerCount);
   int *networkHeights = new int[hiddenLayerCount + 2];
   networkHeights[0] = inputSpaceLength;
   networkHeights[hiddenLayerCount + 1] = outputSpaceLength;
   for(int i = 1; i < hiddenLayerCount + 1; i++){
       networkHeights[i] = hiddenLayers[i-1];
   }
    delete toReturn->network;
    toReturn->network = new Network((this->hiddenLayerCount)+2,networkHeights);
    return toReturn;
}

//also get the tile at the end of each ray
double* MazeController::genInputSpace(int agentNumber) {
    MazeAgent* currentAgent = dynamic_cast<MazeAgent *>(this->agents[agentNumber]);
    Maze* currentMaze = currentAgent->maze;
    int mazeSight[8];
    currentMaze->getDistance(mazeSight);
    //static_cast<double>(mazeSight[0]),static_cast<double>(mazeSight[1]),static_cast<double>(mazeSight[2]),static_cast<double>(mazeSight[3])
    double *inputs = new double[10 + this->dim[0] * this->dim[1]]{static_cast<double>(currentMaze->getCurrent()[0]),static_cast<double>(currentMaze->getCurrent()[1])};
    for(int k = 0; k < 8; k++){
        inputs[2+k] = static_cast<double>(mazeSight[k]);
    }
    int length = currentMaze->getDimensions()[0], height = currentMaze->getDimensions()[1];
    int **heatMap = currentAgent->heatMap;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < length; j++){
            inputs[6 + i * height + j] = heatMap[i][j];
        }
    }
    return inputs;
}

int MazeController::state(double *output, int agentNumber) {
    //find greatest output;
    int best = 0;
    for(int i = 1; i < 4; i++){
        if(output[i] > output[best]){
            best = i;
        }
    }
    int move[2];
    switch(best){
        case 0:
            move[0] = 0;
            move[1] = -1;
            break;
        case 1:
            move[0] = 1;
            move[1] = 0;
            break;
        case 2:
            move[0] = 0;
            move[1] = 1;
            break;
        case 3:
            move[0] = -1;
            move[1] = 0;
            break;
    };
    MazeAgent* currentAgent = dynamic_cast<MazeAgent *>(this->agents[agentNumber]);
    return currentAgent->calcReward(move);
}

Maze *MazeController::makeMaze() {
    return new Maze(this->dim,this->cur,this->currentMaze);
    //return nullptr;
}
//print heatmap to console
void MazeAgent::printHeatMap(){
    int length = maze->getDimensions()[0];
    for(int i = 0; i < maze->getDimensions()[1]; i++){
        for(int j = 0; j < length; j++){
           std::cout << heatMap[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int MazeAgent::calcReward(int *move) {
    this->moves++;
    int result = this->maze->move(move);
    int reward = 0;
    if(result == -1){
        reward = -500;
        //this->reward = reward;
    }else if(result == 0){
        reward+=6;
    }else{
        reward += 1000-this->moves;
    }
    //check if agent is just walking in same pattern over and over;
    int *coords = this->maze->getCurrent();
    if(this->reward >= 0){
        //std::cout << "possible problem" << std::endl;
    }
    reward -= ((heatMap[coords[1]][coords[0]])++);
    //this->reward = reward;
    return reward;
}

bool MazeAgent::endState() {
    //this->moves++;
    int *pos = maze->getCurrent();
    int posA[2];
    posA[0] = pos[0];
    posA[1] = pos[1];
    return !(maze->getTile(posA) == 2 || this->moves >= 100);
    //return Agent::endState();
}

//TODO: Investigate ways to speed this function up
void MazeController::reset() {
    static std::uniform_int_distribution<int> unif(0,this->mazes - 1);
    static std::default_random_engine re;
    int randomNum = unif(re);
    //std::cout << randomNum << std::endl;
    this->currentMaze = this->mazeData[randomNum];
    for(int agentNum = 0; agentNum < this->agentCount; agentNum++){
        MazeAgent* agent = static_cast<MazeAgent *>(this->agents[agentNum]);
        delete agent->maze;
        agent->reward = 0;
        agent->moves = 0;
        agent->maze = this->makeMaze();
        int length = agent->maze->getDimensions()[0];
        for(int i = 0; i < agent->maze->getDimensions()[1]; i++){
            delete[] agent->heatMap[i];
            agent->heatMap[i] = new int[length];
            for(int j = 0; j < length; j++){
                agent->heatMap[i][j] = 0;
            }
        }
    }
}

