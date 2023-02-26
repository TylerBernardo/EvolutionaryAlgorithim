#include <iostream>
#include <Eigen/Dense>
#include "newNetwork.h"
#include "maze.h"

using namespace Eigen;

int main() {
    int length = 3;
    int height[3] = {4,3,4};
    //Network myNetwork = {length,height};
    //myNetwork.calc(input,output);
    //myNetwork.clearMemory();
    void (*genInputSpace)(int *);
    int mazeTemp[25] = {0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 2, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1};
    int dimensionsTemp[2] = {5,5};
    int start[2] = {2,2};
    int stop[2] = {0,2};
    Maze myMaze = {dimensionsTemp, start, stop,mazeTemp};
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
