#include <iostream>
#include <Eigen/Dense>
#include "newNetwork.h"
#include "maze.h"
#include "mazeAgent.h"
#include "evo.h"

using namespace Eigen;
//https://www.jetbrains.com/help/clion/apply-changes-from-one-branch-to-another.html#merge
int main() {
    int length = 5;
    int *height = new int[length]{10,6,6,6,10};
    //Network myNetwork = {length,height};
    //myNetwork.calc(input,output);
    //myNetwork.clearMemory();
    //void (*genInputSpace)(int *);
    int mazeTemp[25] = {0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 2, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1};
    int dimensionsTemp[2] = {5,5};
    int start[2] = {2,2};
    int stop[2] = {0,2};
    Maze myMaze = {dimensionsTemp, start, stop,mazeTemp};
    int populationSize = 100;
    int generations = 10000;
    MazeController mazeC = {3,height,populationSize,dimensionsTemp,start,stop,mazeTemp};
    //myMaze.print();
    MazeAgent* best = dynamic_cast<MazeAgent *>(learn(&mazeC, populationSize, generations));
    mazeC.reset(0);
    do{
        //evaluate the agent's network on the current state
        double* output = new double[mazeC.outputSpaceLength];
        best->network->calc(mazeC.genInputSpace(0),mazeC.inputSpaceLength,output, mazeC.outputSpaceLength);
        best->maze->print();
        std::cout << std::endl << "----------" << std::endl;
        int reward = mazeC.state(output,0);
        //process reward here
        best->reward += reward;
    }while(best->endState());
    /*
    std::cout << std::endl;
    myMaze.print();
    int distance[4] = {0,0,0,0};
    myMaze.getDistance(distance);
    std::cout << std::endl;
    for(int i = 0; i < 4; i++){
        std::cout << distance[i] << " ";
    };
     */
    return 0;
}
