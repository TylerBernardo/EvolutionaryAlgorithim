//
// Created by tyler on 3/7/2023.
//

#ifndef EVOLUTIONARYALGORITHIM_MAZEAGENT_H
#define EVOLUTIONARYALGORITHIM_MAZEAGENT_H
#include "evo.h"
#include "maze.h"

class MazeAgent : public Agent{
    public:
        Maze *maze;
        int ** heatMap;
        int moves = 0;
        MazeAgent(){
            maze = nullptr;
        }

        MazeAgent(Maze * _maze,int _inputSpaceLength,int _outputSpaceLength,int _hiddenLayerCount){
            this->inputSpaceLength = _inputSpaceLength;
            this->outputSpaceLength = _outputSpaceLength;
            this->hiddenLayerCount = _hiddenLayerCount;
            this->maze = _maze;
            heatMap = new int* [maze->getDimensions()[1]];
            int length = maze->getDimensions()[0];
            for(int i = 0; i < maze->getDimensions()[1]; i++){
                heatMap[i] = new int[length];
                for(int j = 0; j < length; j++){
                    heatMap[i][j] = 0;
                }
            }
        }

        bool endState() override;

        void printHeatMap() override;

        int calcReward(int move[2]);

        ~MazeAgent(){
            for(int i = 0; i < maze->getDimensions()[1]; i++){
                delete[] heatMap[i];
            }
            delete[] heatMap;
            delete[] maze;
            delete network;
        }
};

class MazeController : public EvoController{
    int dim[2];
    int cur[2];
    int **mazeData;
    int* currentMaze;
    int mazes;
    public:
        //MazeAgent **agents;
        MazeController(int _hiddenLayerCount, int* _hiddenLayers, int _agentCount,int (&_dim)[2], int (&_cur)[2], int **_mazeData, int _mazes){
            this->dim[0] = _dim[0];
            this->dim[1] = _dim[1];
            this->cur[0] = _cur[0];
            this->cur[1] = _cur[1];
            this->mazeData = _mazeData;
            this->inputSpaceLength = 10 + _dim[0] * _dim[1];
            this->outputSpaceLength = 4;
            this->hiddenLayerCount = _hiddenLayerCount;
            this->hiddenLayers = _hiddenLayers;
            this->agentCount = _agentCount;
            this-> agents = new Agent *[this->agentCount];
            this -> currentMaze = mazeData[0];
            this-> mazes = _mazes;
            for(int i = 0; i < agentCount; i++){
                agents[i] = this->createAgent();
            }
        }

        double* genInputSpace(int agentNumber) override;
        //should take in the output of the neural net and determine what action to take. Should take that action, then return score. also in charge of termination the simulation.
        int state(double *output, int agentNumber) override;
        //creates an agent
        MazeAgent* createAgent() override;

        void reset() override;

        Maze* makeMaze();

        ~MazeController(){
            for(int i = 0; i < agentCount; i++){
                delete &agents[i];
            }
            delete[] agents;
        }
};
#endif //EVOLUTIONARYALGORITHIM_MAZEAGENT_H
