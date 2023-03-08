//
// Created by tpixe on 5/4/2022.
//

#include "maze.h"
#include <iostream>

int* Maze::getCurrent() {
    return this->current;
}

Maze::Maze(int (&dim)[2],int (&cur)[2],int (&end)[2], int * maze){
        dimensions[0] = dim[0];
        dimensions[1] = dim[1];
        this->end[0] = end[0];
        this->end[1] = end[1];
        current[0] = cur[0];
        current[1] = cur[1];
        std::cout << current[0] << " " << current[1] << std::endl;
        this->maze = new int*[dim[1]];
        for(int i= 0; i < dim[1]; i++){
            this->maze[i] = new int[dim[0]];
            for(int j = 0; j < dim[0]; j++){
                this->maze[i][j] = maze[j + i * dim[0]];
            }
        }
    };

//casts rays in 8 directions, starting at (0,-1) and moving clockwise
//[UP, RIGHT, DOWN, LEFT]
void Maze::getDistance(int (&distance)[4]){
        int directions [4][2] = {{0,-1},{1,0},{0,1},{-1,0}};
        for(int i = 0; i < 4; i++){
            bool done = false;
            int k = 1;
            do{
                int newMove[2] = {current[0] + directions[i][0] * k,current[1] + directions[i][1] * k};
                int result = getTile(newMove);
                if(result == -1 || result == 1){
                    done = true;
                    distance[i] = k-1;
                }else{
                    k++;
                }
            }while(!done);
        }
    };

int Maze::getTile(int (&move)[2]){
        if(move[0] > dimensions[0]-1 || move[1] > dimensions[1]-1 || move[0] < 0 || move[1] < 0){
            return -1;
        }
        return maze[move[1]][move[0]];
    };

void Maze::print(){
        for(int r = 0; r < dimensions[1]; r++){
            for(int c = 0; c < dimensions[0]; c++){
                if(r == current[1] && c == current[0]){
                    std::cout << "P ";
                }else{
                    std::cout << maze[r][c] << " ";
                }

            }
            std::cout << std::endl;
        }
    };


int Maze::move(int dir[2]){
    int newPos[2] = {current[0] + dir[0], current[1] + dir[1]};
    int check = getTile(newPos);
    if(check == 0 || check == 2){
        current[0] = newPos[0];
        current[1] = newPos[1];
        return check;
    }else{
        return -1;
    }
}

int *Maze::getDimensions() {
    return this->dimensions;
}
