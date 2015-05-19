/*
  main.cpp
  lab10

  Created by Oleksii Kyrylchuk on 5/19/15.
  Copyright (c) 2015 olety. All rights reserved.

 
 Implement graph representation as an adjacency matrix.
 In the tasks vertices a numbered from 0. Any graph is without loops (a loop is an edge form a vertex to this same vertex)
 
 */

#include <iostream>
#include <sstream>
#include <float.h>
#include <vector>

class Graph {
private:
    std::vector<std::vector<double>> nodeMatrix;
public:
    Graph( int nodes );
    ~Graph();
    void insertEdge( int edge1, int edge2, double weight );
    bool findEdge( int edge1, int edge2, double &weight );
    void showAsMatrix();
    void showAsArray();
};

Graph::Graph ( int nodes ){
    this->nodeMatrix.resize((size_t) nodes);
    for ( int i = 0; i < nodes; i++ ){
        this->nodeMatrix[i].resize((size_t) nodes);
        for ( int j = 0; j < nodes; j++ ){
            if ( i == j ){
                this->nodeMatrix[i][j] = 0;
                continue;
            }
            this->nodeMatrix[i][j] = DBL_MAX;
        }
    }
}

Graph::~Graph (){
    
}

void Graph::insertEdge( int edge1, int edge2, double weight){

}

bool Graph::findEdge( int edge1, int edge2, double &weight){
    return false;
}

void Graph::showAsMatrix(){

}

void Graph::showAsArray(){

}

bool isCommand(const std::string command,const char *mnemonic){
    return command==mnemonic;
}

int main(){
    std::string line;
    std::string command;
    int currentT=0;
    bool retBool = false;
    Graph *g = NULL;
    int value1=0, value2=0, value3 = 0;
    std::cout << "START" << std::endl;
    while(true){
        getline(std::cin,line);
        std::stringstream stream(line);
        stream >> command;
        if(line=="" || command[0]=='#')
        {
            // ignore empty line and comment
            continue;
        }
        
        // copy line on output with exclamation mark
        std::cout << "!" << line << std::endl;
        
        // change to uppercase
        command[0]=toupper(command[0]);
        command[1]=toupper(command[1]);
        
        // zero-argument commands
        
        if(isCommand(command,"HA")){
            std::cout << "END OF EXECUTION" << std::endl;
            break;
        }
        
        if(isCommand(command,"SM")) // Show as a matrix
        {
            continue;
        }
        
        if(isCommand(command,"SA")) // Show as an array of lists
        {
            continue;
        }
        
        // read next argument, one int value
        stream >> value1;
        
        if(isCommand(command,"GO"))
        {
            g = new Graph[value1];
            continue;
        }
        
        if(isCommand(command,"CH"))
        {
            currentT = value1;
            continue;
        }
        
        //read 2nd argument
        stream >> value2;
        
        if(isCommand(command,"LG")) //loadGraph
        {
            continue;
        }
        
        if(isCommand(command,"FE")) //findEdge
        {
            continue;
        }
        
        //read 3rd argument
        stream >> value3;
        
        if(isCommand(command,"IE")) //insertEdge
        {
            continue;
        }
        
        std::cout << "wrong argument in test: " << command << std::endl;
    }
    delete[] g;
}
