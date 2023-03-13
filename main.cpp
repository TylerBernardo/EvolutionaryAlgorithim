#include <iostream>
#include <Eigen/Dense>
#include "newNetwork.h"
#include "maze.h"
#include "mazeAgent.h"
#include "evo.h"

using namespace Eigen;
//https://www.jetbrains.com/help/clion/apply-changes-from-one-branch-to-another.html#merge
//719 total lines
int main() {
    int length = 7;
    int *height = new int[length]{30,30,20,15,15,20,30};
    //Network myNetwork = {length,height};
    //myNetwork.calc(input,output);
    //myNetwork.clearMemory();
    //void (*genInputSpace)(int *);
    int mazeTemp[25] = {0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 2, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1};
    int mazeTwo[25] = {0,0,0,0,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,2};
    int mazeThree[25] = {0,1,0,0,2,1,1,0,1,0,0,0,0,0,0,0,1,0,1,1,0,0,0,1,0};
    int mazeCount = 3;
    int **mazes = new int*[mazeCount]{mazeTemp,mazeTwo,mazeThree};
    int dimensionsTemp[2] = {5,5};
    int start[2] = {2,2};
    Maze myMaze = {dimensionsTemp, start,mazeTemp};
    int populationSize = 200;
    int generations = 10000;
    MazeController mazeC = {5,height,populationSize,dimensionsTemp,start,mazes,mazeCount};
    //myMaze.print();
    MazeAgent* best = dynamic_cast<MazeAgent *>(learn(&mazeC, populationSize, generations,24));
    mazeC.reset();
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
    best->printHeatMap();
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
