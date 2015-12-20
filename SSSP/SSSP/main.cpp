/*
 main.cpp
 lab12
 
 Created by Oleksii Kyrylchuk on 5/19/15.
 Copyright (c) 2015 olety. All rights reserved.
 
 */

#include <iostream>
#include <sstream>
#include "spGraph.h"

bool isCommand( const std::string command, const char *mnemonic ){
    return command==mnemonic;
}

int main(){
    std::string line,command;
    int currentG = 0, i, value1, value2, k;
    double value3;
    //    bool retBool = false;
    std::vector<spGraph*> g;
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
        
        if(isCommand(command,"HA")){ // halt exec
            std::cout << "END OF EXECUTION" << std::endl;
            break;
        }
        
        if(isCommand(command,"SM")){ // Show as a matrix
            g[currentG]->showAsMatrix();
            continue;
        }
        
        if(isCommand(command,"SA")){ // Show as an array of lists
            g[currentG]->showAsArray();
            continue;
        }
        
        // read next argument, one int value
        stream >> value1;
        
        if(isCommand(command,"GO")){ // make x arrays of graphs
            g.resize(value1);
            continue;
        }
        
        if(isCommand(command,"SS")){ // SSSP
            g[currentG]->printSP(value1);
            continue;
        }
        
        if(isCommand(command,"CH")){ //choose graph
            currentG = value1;
            continue;
        }
        
        //read 2nd argument
        stream >> value2;
        
        if(isCommand(command,"LG")){ //loadGraph, value1 = nodes, value2 = edges
            g[currentG] = new spGraph( value1 );
            k = value2;
            for ( i = 0; i < k; i++ ){
                getline(std::cin,line);
                std::stringstream stream(line);
                stream >> value1 >> value2 >> value3;
                g[currentG]->insertEdge(value1, value2, value3);
            }
            continue;
        }
        
        if(isCommand(command,"FE")){ //findEdge
            if ( !(g[currentG]->findEdge(value1, value2, value3))){ //should it return val, if node1==node2?
                std::cout << "false" << std::endl;
                continue;
            }
            std::cout << value3 << std::endl;
            continue;
        }
        
        //read 3rd argument
        stream >> value3;
        
        if(isCommand(command,"IE")){ //insertEdge
            g[currentG]->insertEdge(value1, value2, value3);
            continue;
        }
        
        std::cout << "wrong argument in test: " << command << std::endl;
    }
}
