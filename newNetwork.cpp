//
// Created by tpixe on 5/3/2022.
//

#include <iostream>
#include "newNetwork.h"

inline double sigmoid(double x){
    return ((x/(1+abs(x)))+1)/2;
}

inline void sigmoidVector(MatrixXd &input, int height){
    for(int i = 0; i < height; i++){
        input(i) = sigmoid(input(i));
    }
}

Network::Network() {

}

Network::Network(int length, int *height){
        srand (static_cast <unsigned> (time(0)));
        this->length = length;
        this->height = height;
        weights = new MatrixXd[length - 1];
        bias = new MatrixXd[length];
        inputs = new VectorXd[length];
        for(int i = 0; i < length; i++){
            if(i > 0){
                MatrixXd wToAdd = MatrixXd::Random(height[i], height[i-1]) * 5;
                weights[i- 1] = wToAdd;
                MatrixXd bToAdd = MatrixXd::Random(height[i],1) * 5;
                bias[i-1] = bToAdd;
            }
            VectorXd iToAdd = VectorXd::Constant(height[i],0);
            inputs[i] = iToAdd;
        }
    };

Network::~Network(){
    delete[] weights;
    delete[] bias;
    delete[] inputs;
}

void Network::clearMemory(){
    delete[] weights;
    weights = nullptr;
    delete[] bias;
    bias = nullptr;
    delete[] inputs;
    inputs = nullptr;
}

void Network::print(){
        for(int i = 0; i < length-1; i++){
            std::cout << "This is for the area between " << i << " and " << i + 1 << ". " << "Weights : " << std::endl << weights[i] << std::endl << " Bias: " << std::endl << bias[i] << std::endl;
        }
    };

void Network::calc(VectorXd &input, MatrixXd &output){
    inputs[0] = input;
    for(int i = 0; i < length-1; i++){
        MatrixXd result = weights[i] * inputs[i];
        result = result + bias[i];
        sigmoidVector(result,height[i+1]);
        inputs[i+1] = result;
    }
    output = inputs[length-1];
}

void Network::generateDNA() {
    //loop through each weight, then each bias, and add their value to the dna
    //calculate size of dna array.
    //int size = 0;
    //DNA has to be cleared from memory outside this object, kept in order to be used for mutation or other things. Might change this later
    for(int i = 0; i < length-1; i++){
        size += weights[i].rows() * weights[i].cols();
        size += bias[i].rows() * bias[i].cols();
    }
    dna = new double[size];
    //add weights
    int current = 0;
    for(int i = 0; i < length-1; i++){
        int rows = weights[i].rows();
        for(int r = 0; r < rows; r++){
            int cols = weights[i].cols();
            for(int c = 0; c < cols; c++){
                dna[current + c + r * cols] = weights[i](r,c);
            }
        }
        current += weights[i].rows() * weights[i].cols();
    }
    for(int i = 0; i < length-1; i++){
        int rows = bias[i].rows();
        for(int r = 0; r < rows; r++){
            int cols = bias[i].cols();
            for(int c = 0; c <  cols; c++){
                dna[current + c + r * cols] = bias[i](r,c);
            }
        }
        current += bias[i].rows() * bias[i].cols();
    }
    /*
    for(int i = 0; i < size; i++){
        std::cout << dna[i] << std::endl;
    }
     */
}

void Network::convert(std::string& output){
    for(int i = 0; i < size; i++){
        output += std::to_string(dna[i]) + " | ";
    }
    std::cout << output;
};

void Network::convert(std::string* input,double* output){};