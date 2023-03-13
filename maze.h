//
// Created by tpixe on 5/4/2022.
//

#ifndef EVOLUTIONARYALGORITHIM_MAZE_H
#define EVOLUTIONARYALGORITHIM_MAZE_H

class Maze {
    //xy
    int dimensions[2];
    int current[2] = {0, 0};
    int **maze;

public:
    Maze(int (&dim)[2], int (&cur)[2], int *maze);
    ~Maze(){
        for(int i = 0; i < this->dimensions[1]; i++){
            delete[] this->maze[i];
        }
        delete[] this->maze;
    }
    void getDistance(int (&distance)[8]);

    int getTile(int (&move)[2]);

    void print();

    int move(int dir[2]);

    int* getCurrent();

    int* getDimensions();
};
#endif //EVOLUTIONARYALGORITHIM_MAZE_H
