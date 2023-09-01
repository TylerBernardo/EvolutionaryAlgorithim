#include <iostream>
#include <Eigen/Dense>
#include "newNetwork.h"
#include "maze.h"
#include "mazeAgent.h"
#include "evo.h"
#include <fstream>
#include <vector>

using namespace Eigen;

const std::string PATH = R"(C:\Users\tyler\CLionProjects\EvolutionaryAlgorithim\)";

//https://www.jetbrains.com/help/clion/apply-changes-from-one-branch-to-another.html#merge
//719 total lines
//TODO: cache ai progress every X generations so training can be paused
int ** readMazesFromFile(std::string const &path, int mazeSize, int &mazeCount){
    std::ifstream file;
    file.open(path);
    std::vector<int*> output;
    std::string line;
    int lines = 0;
    while ( std::getline(file, line) ){
        ++lines;
        int* currentMaze = new int[mazeSize];
        for(int i = 0; i < mazeSize; i++){
            currentMaze[i] = int(line[1+2*i]) - 48;
        }
        output.push_back(currentMaze);
    }
    int** outputA = new int*[lines];
    for(int n = 0; n < lines; n++){
        outputA[n] = output[n];
    }
    file.close();
    mazeCount = lines;
    return outputA;
}

int main() {
    //TODO: Explore crashes on length > 8 also seems related to large size of network size. Crash almost seems random and based on segfault on maze data
    int length = 8;
    int *height = new int[length]{400,230,150,130,100,100,100,75};
    int mazeCount = 1;
    int dimensionsTemp[2] = {19,19};
    int **mazes = readMazesFromFile(PATH + "output.txt",19*19,mazeCount);//new int*[mazeCount]{newMazeOne};//{mazeTemp,mazeTwo,mazeThree};
    int start[2] = {0,0};
    int populationSize = 50;
    int generations = 1;
    MazeController mazeC = {5,height,populationSize,dimensionsTemp,start,mazes,mazeCount};
    //myMaze.print();

    //mazeC.save(PATH + "save.txt");
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
    return 0;
}
